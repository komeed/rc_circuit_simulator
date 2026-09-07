//
// Created by Omeed on 9/5/26.
//

#include "matrix.h"

#include <cfloat>
#include <cstdlib>
#include <cstdio>
#include <vector>



matrix::matrix(int num_row, int num_col): m(num_row), n(num_col) {
    backing_arr = new float[m*n]();
}
matrix::matrix(int num_row, int num_col, float* mat) {
    m = num_row;
    n = num_col;
    backing_arr = new float[m*n]();
    memcpy(backing_arr, mat, m*n*sizeof(float));
}

void matrix::print() const {
    for (int i = 0; i < m; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf("%f", backing_arr[i*n + j]);
            if (j < n - 1){
                printf(" ");
            }
        }
        printf("]\n");
    }
}

#define SWAP_ROWS_AUGMENTED(A, b, r1, r2) do { \
(A)->swap_rows((r1), (r2));           \
(b)->swap_rows((r1), (r2));           \
} while(0)

void matrix::swap_rows(int r1, int r2) const {
    if (r1 == r2) {
        return;
    }
    for (int i = 0; i < n; i++) {
        float temp = backing_arr[r1*n + i];
        backing_arr[r1*n + i] = backing_arr[r2*n + i];
        backing_arr[r2*n + i] = temp;
    }
}

#define SCALE_ROWS_AUGMENTED(A, b, r1, scale) do { \
(A)->scale_row((r1), (scale));           \
(b)->scale_row((b), (r1), (scale));           \
} while(0)

void matrix::scale_row(int r1, float scale) const {
    int offset = r1*n;
    for (int i = 0; i < n; i++) {
        backing_arr[offset + i] *= scale;
    }
}

#define ADD_ROWS_AUGMENTED(A, b, ground_r, add_r) do { \
(A)->add_row((ground_r), (add_r));           \
(b)->add_row((ground_r), (add_r));           \
} while(0)

void matrix::add_row(int ground_r, int add_r) const {
    for (int i = 0; i < n; i++) {
        backing_arr[ground_r*n + i] += backing_arr[add_r*n + i];
    }
}

void matrix::subtract_row(int ground_r, int add_r) const {
    for (int i = 0; i < n; i++) {
        backing_arr[ground_r*n + i] -= backing_arr[add_r*n + i];
    }
}

//do subtract/addition operation on two rows
void matrix::finish_row(matrix* aug, int ground_r, int add_r, int pivot_col) const {
    int pos1 = ground_r*n + pivot_col;
    int pos2 = add_r*n + pivot_col;
    float val1 = backing_arr[pos1];
    float val2 = backing_arr[pos2];
    //first find scale_factors for add row such that they will match
    float scale_factor = val1 / val2;
    //then, scale and subtract
    for (int i = 0; i < n - pivot_col; i++) {
        backing_arr[pos2 + i] *= scale_factor;
        backing_arr[pos2 + i] -= backing_arr[pos1 + i];
    }
    aug->scale_row(add_r, scale_factor);
    aug->subtract_row(add_r, ground_r); // the opposite because we want to subtract add from ground to keep ground
}

//solve_matrix currenetly only works with nxn matrices (square) (otherwise you will encounter problems?)
void matrix::solve_matrix(matrix* other) {
    if (this->m != other->m) {
        fprintf(stderr,"invalid matrix mult!\n");
        return;
    }
    //matrix* x = new matrix(n, 1);
  /*  //initialize a array with indices corrresponding to row index of that number of leading zeroes
    int leading_zeros_arr[m];*/
    //I guess the first step is finding
    //the column that has the highest one?

    //leading_col is the first column during each iteration after zeroes
    int pivot_row = 0;
    int pivot_col = 0;
    while (pivot_row < m) {
        float max_first = 0;
        int max_row = 0;
        for (int i = pivot_row; i < m; i ++) {
            int first_col = i * n + pivot_col;
            float first_col_val = ABS(backing_arr[first_col]);
            if (max_first < first_col_val) {
                max_first = first_col_val;
                max_row = i;
            }
        }
        //if this every happens where there is a free variable, I guess there's no solution?
        if (max_first == 0) {
            fprintf(stderr, "There is a free variable, which means infinite solutions. something's not right.\n");
            return;
        }
        SWAP_ROWS_AUGMENTED(this, other, pivot_row, max_row);
        printf("\n after swapping: \n");
        // print();
        // other->print();
        for (int row = pivot_row + 1; row < m; row++) {
            //now, go through next rows and if leading is not zero, run operation
            int first_col = row * n + pivot_col;
            if (backing_arr[first_col] != 0) {
                finish_row(other, pivot_row, row, pivot_col);
            }
            //print();
            //other->print();
        }
        pivot_row++;
        pivot_col++;
    }
    // now that we have it in gauss format we can solve the other matrix
    //first, add all the variables solved from the previous steps
    int val = n - 1;
    // i and val represent position (i, i) in the matrix
    for (int i = val; i >= 0; i--) {
        //first solve that variable
        float solved_val = other->divide_val(i, 0, backing_arr[i*n + i]);
        //then, subtract each value in each spot to the one above
        for (int next_row = i - 1; next_row >= 0; next_row--) {
            float backing_arr_val = backing_arr[next_row*n + i];
            other->subtract_val(next_row, 0, backing_arr_val * solved_val);
        }
    }
}

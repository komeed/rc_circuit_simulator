//
// Created by Omeed on 9/5/26.
//

#ifndef MATRIX_H
#define MATRIX_H



class matrix {
    int m; // rows
    int n; // cols
    float* backing_arr;
public:
    matrix(int num_row, int num_col);
    matrix(int num_row, int num_col, float* mat);
    //all of these are relative to 1! not zero!
    void add_val_normal(int row, int col, float val) { backing_arr[(row - 1)*n + (col - 1)] += val; }
    void subtract_val(int row, int col, float val) { backing_arr[(row)*n + (col)] -= val; }
    void set_val_normal(int row, int col, float val) { backing_arr[(row - 1)*n + (col - 1)] = val; }
    float get_val_normal(int row, int col) { return backing_arr[(row - 1)*n + (col - 1)]; }
    float divide_val(int row, int col, float val) { return (backing_arr[(row) * n + (col)] /= val); }
    void print() const;

    void swap_rows(int r1, int r2) const;
    void scale_row(int r1, float scale) const;
    void add_row(int source, int add) const;
    void subtract_row(int ground_r, int add_r) const;
    void finish_row(matrix* aug, int ground_r, int add_r, int pivot_col) const;


    void solve_matrix(matrix* other);
};



#endif //MATRIX_H

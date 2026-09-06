#include <iostream>
#include "circuit.h"
#include "parser/netlist_parser.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    //circuit cir = circuit();
    circuit *cir = parse_netlist_c("../netlist.rc");
    if (cir == NULL) {
        fprintf(stderr, "circuit is null oops");
        return 0;
    }
    auto x = cir->solve_circuit();

    printf("\nfinal result matrix:\n");
    x->print();
}

#include <iostream>
#include "circuit.h"
#include "parser/netlist_parser.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
void generate_netlist(const std::string& filename, const std::string& gen_path );
int main() {
    //circuit cir = circuit();
    const char* gen_path = "../written_netlist.rc";
    generate_netlist("../untitled.cir", gen_path);
    circuit *cir = parse_netlist_c(gen_path);
    if (cir == NULL) {
        fprintf(stderr, "circuit is null oops");
        return 0;
    }
    auto x = cir->solve_circuit();

    printf("\nfinal result matrix:\n");
    //x->print();
    cir->print_components();
}

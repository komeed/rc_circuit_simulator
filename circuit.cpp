//
// Created by Omeed on 9/3/26.
//

#include "circuit.h"

circuit::circuit() {
    comp_storage = std::vector<component>();
    comp_map = std::unordered_map<component_name, std::unique_ptr<component>>();
}

void circuit::add_component(component c) {
    comp_storage.push_back(c);
    component x =
}
void circuit::add_component(component c, std::string name) {
    comp_storage.push_back(c);
}
void circuit::add_component(component c, std::string name, int num) {
    comp_storage.push_back(c);
}
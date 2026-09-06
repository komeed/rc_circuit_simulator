//
// Created by Omeed on 8/20/26.
//

#include "node.h"

node_t::node_t() : voltage(0), id(0) {
    components = std::vector<component*>();
};
node_t::node_t(int id) : voltage(0), id(id) {
    components = std::vector<component*>();
};

void node_t::add_component(component* comp) {
    if (!comp) {
        fprintf(stderr, "oops component null in node_t");
        return;
    }
    components.push_back(comp);
}
//
// Created by Omeed on 9/5/26.
//

#include "current_source.h"

current_source::current_source(std::string id, float current, node_t* a, node_t* b) : id(id), node_a(a),
node_b(b), current(current) {

}
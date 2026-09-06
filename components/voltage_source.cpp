//
// Created by Omeed on 9/6/26.
//

#include "voltage_source.h"

voltage_source::voltage_source(std::string id, float voltage, node_t* a, node_t* b) : id(id), node_a(a),
node_b(b), voltage(voltage) {

}
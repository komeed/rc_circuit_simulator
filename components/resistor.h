//
// Created by Omeed on 9/3/26.
//

#ifndef RESISTOR_H
#define RESISTOR_H

#include "component.h"
#include "node.h"



class resistor : public component {
public:
    float resistance; // ohms

    COMPONENT_TYPE get_type() override { return COMPONENT_TYPE::RESISTOR; }
    resistor(std::string id, float resistance, node_t* node_a, node_t *node_b);
};

#endif //RESISTOR_H

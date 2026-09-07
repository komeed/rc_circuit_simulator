//
// Created by Omeed on 9/5/26.
//

#ifndef CURRENT_SOURCE_H
#define CURRENT_SOURCE_H

#include "component.h"
#include "node.h"

class current_source : public component {
public:
    float current;
    std::string id;
    node_t* node_a;
    node_t* node_b;

    COMPONENT_TYPE get_type() override { return COMPONENT_TYPE::CURRENT_SOURCE; }
    current_source(std::string id, float current, node_t* a, node_t* b) :
                component(id, 0, a, b), current(current) {}
};



#endif //CURRENT_SOURCE_H

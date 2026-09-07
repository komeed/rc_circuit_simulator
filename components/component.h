//
// Created by Omeed on 9/3/26.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <utility>

#include "node.h"

typedef enum {
    RESISTOR,
    CAPACITOR,
    VOLTAGE_SOURCE,
    CURRENT_SOURCE
} COMPONENT_TYPE;

class component {
public:
    std::string id;
    float voltage;
    node_t* node_a;
    node_t* node_b;
    component(std::string id, float voltage, node_t* a, node_t* b) : id(std::move(id)),voltage(voltage), node_a(a), node_b(b) {}
    virtual COMPONENT_TYPE get_type() = 0;
    virtual ~component() = default;
};

//current carrying component
class cc_component {

};
/*
void connect_components(pin* a, pin* b);*/

#endif //COMPONENT_H

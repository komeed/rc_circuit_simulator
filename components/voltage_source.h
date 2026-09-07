//
// Created by Omeed on 9/6/26.
//

#ifndef VOLTAGE_SOURCE_H
#define VOLTAGE_SOURCE_H

#include "component.h"
#include "string"
#include "node.h"

class voltage_source : public component {
public:

    COMPONENT_TYPE get_type() override { return COMPONENT_TYPE::VOLTAGE_SOURCE; }
    voltage_source(std::string id, float voltage, node_t* a, node_t* b);
};



#endif //VOLTAGE_SOURCE_H

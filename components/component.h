//
// Created by Omeed on 9/3/26.
//

#ifndef COMPONENT_H
#define COMPONENT_H

typedef enum {
    RESISTOR,
    CAPACITOR,
    VOLTAGE_SOURCE,
    CURRENT_SOURCE
} COMPONENT_TYPE;

class component {
public:
    virtual COMPONENT_TYPE get_type() = 0;
    virtual ~component() = default;
};

//current carrying component
class cc_component {

};
/*
void connect_components(pin* a, pin* b);*/

#endif //COMPONENT_H

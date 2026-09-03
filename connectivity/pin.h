//
// Created by Omeed on 8/20/26.
//

#pragma once

#ifndef PIN_H
#define PIN_H

#include "vector"
#define INIT_PIN_ARR_CAPACITY 10
#define PIN_ARR_R_FACTOR 1.5

//basiclaly the problem is, how can we go from a pin class to a component? and know the component's type
// basically instantly? (we're not just doing a million dynamic casts)

class node;
class component;

class pin {
private:
   // uint32_t ID; // unique id assigned to pin correlating to position in global pin array
    //uint32_t is_sink; // if it is a sink, voltage can't pass through it
    //if it isn't a sink, you can try dynamic casts to find the actual component it's referencing
    component* parent_comp;
    float voltage;
public:
    node* wired_net;
    pin(component* comp);
    void connect_to_pin(pin* other);
};

class global_pin_arr {
private:
    pin** pins;
    uint32_t size;
    uint32_t capacity;
    void resize_pin_arr();
public:
    global_pin_arr();
    uint32_t add_pin_to_arr(pin* pin);
};

class node {
    std::vector<pin*> pins; // pins connected to the net
    float voltage; // nets hold voltage
public:
    node();
    void add_pin(pin* pin);
};

#endif //PIN_H

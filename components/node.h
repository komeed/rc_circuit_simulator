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

class component;
class node_t {
    std::vector<component*> components;
    float voltage;
public:
    int id;
    node_t();
    node_t(int id);
    void add_component(component* comp);
};

#endif //PIN_H

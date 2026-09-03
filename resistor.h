//
// Created by Omeed on 9/3/26.
//

#ifndef RESISTOR_H
#define RESISTOR_H

#include "component.h"
#include "connectivity/pin.h"



class resistor : public component {
    float resistance; // ohms
    pin pin_a;
    pin pin_b;

public:
    resistor(float resistance);
};

#endif //RESISTOR_H

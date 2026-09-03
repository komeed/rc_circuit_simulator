//
// Created by Omeed on 9/3/26.
//

#include "resistor.h"

resistor::resistor(float resistance): pin_a(this), pin_b(this) {
    this->resistance = resistance;
}

//
// Created by Omeed on 9/3/26.
//

#include "resistor.h"

resistor::resistor(std::string id, float resistance, node_t* node_a, node_t* node_b): component(id, 0, node_a, node_b), resistance(resistance) {

}

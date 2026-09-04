//
// Created by Omeed on 9/3/26.
//

#include "component.h"

#include "connectivity/pin.h"

void connect_components(pin* a, pin* b) {
    if (!a->wired_node && !b->wired_node) {
        node_t* node = new node_t();
        a->wired_node = node;
        b->wired_node = node;
        node->add_pin(a);
        node->add_pin(b);
    }
    else if (!a->wired_node && b->wired_node) {
        a->wired_node = b->wired_node;
        b->wired_node->add_pin(a);
    }
    else if (a->wired_node && !b->wired_node) {
        b->wired_node = a->wired_node;
        a->wired_node->add_pin(b);
    }
    else if (a->wired_node && b->wired_node && (a->wired_node != b->wired_node)) {
        //if both already have nodes, move pins from b node to a node
        node_t* node = a->wired_node;
        node_t* temp_b_node = b->wired_node;
        node->move_pins_from(b->wired_node);
        delete temp_b_node;
    }
}
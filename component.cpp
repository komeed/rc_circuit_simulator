//
// Created by Omeed on 9/3/26.
//

#include "component.h"

#include "connectivity/pin.h"

void connect_components(pin* a, pin* b) {
    if (!a->wired_net && !b->wired_net) {
        node* net = new node();
        a->wired_net = net;
        b->wired_net = net;
        net->add_pin(a);
        net->add_pin(b);
    }
    else if (!a->wired_net && b->wired_net) {
        a->wired_net = b->wired_net;
        b->wired_net->add_pin(a);
    }
    if (a->wired_net) {
        if (!b->wired_net) {
            //set b->wired_net to a->net
            b->wired_net = a->wired_net;
        }
        else {

        }
    }
    else if (b->wired_net) {
        a->wired_net = b->wired_net;
    }
    else {

    }
}
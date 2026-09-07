//
// Created by Omeed on 9/5/26.
//

#ifndef NETLIST_PARSER_H
#define NETLIST_PARSER_H
#include "fstream"
#include "sstream"
#include "../circuit.h"
#include "../components/current_source.h"
#include "../components/voltage_source.h"

#define ATOI_NULL -2
#define GROUND_NODE_NUM -1

inline int safe_atoi(char* c) {
    if (c == NULL) {
        fprintf(stderr, "huh that's weird");
        return ATOI_NULL;
    }
    int x = atoi(c);
    if (x == 0) {
        fprintf(stderr, "oops string to int conversion failed");
        return ATOI_NULL;
    }
    return x;
}

inline circuit* parse_netlist_c(const char* path) {
    // the path is relative
    circuit *c = new circuit();
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Couldn't open file oops");
        delete c;
        return nullptr;
    }
    //strcmp for comparing
    char line[256];
    uint8_t contains_ground_node = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, " ");
        if (token == NULL || token[0] == '#') {
            continue;
        }
        //retrieve the other data of the line (id, etc)
        char* id = strtok(NULL, " ");
        int node_a, node_b;
        //we might have -1 be like invalid node or something when something is only 1 node
        if ((node_a = safe_atoi(strtok(NULL, " "))) == ATOI_NULL || (node_b = safe_atoi(strtok(NULL, " "))) == ATOI_NULL) {
            delete c;
            return NULL;
        }
        node_t* a = c->contains_add_node(node_a);
        node_t* b = c->contains_add_node(node_b);
        //now a and b have to be not null
        if (a == nullptr || b == nullptr) {
            fprintf(stderr, "a or b is null, this means it wasn't created!");
        }
        if (a->id == GROUND_NODE_NUM || b->id == GROUND_NODE_NUM) {
            contains_ground_node = 1;
        }
        char* value = strtok(NULL, " ");
        if (token[0] == 'R') {
            //resistor (value is float)
            float resistance = std::strtof(value, nullptr); // I trust it's right?
            if (resistance == 0.0) {
                fprintf(stderr, "either resistance can't be 0 or failed parsing)");
                delete c;
                return NULL;
            }
            c->add_component(std::make_unique<resistor>(id, resistance, a, b));
        }
        //current source!! for now we're treating other side as ground
        else if (token[0] == 'I') {
            float current = std::strtof(value, nullptr);
            if (current == 0.0) {
                fprintf(stderr, "either current can't be 0 or failed parsing)");
                delete c;
                return NULL;
            }
            c->add_component(std::make_unique<current_source>(id, current, a, b));
        }
        else if (token[0] == 'V') {
            float voltage = std::strtof(value, nullptr);
            if (voltage == 0.0) {
                fprintf(stderr, "either voltage can't be 0 or failed parsing");
                delete c;
                return NULL;
            }
            c->add_component(std::make_unique<voltage_source>(id, voltage, a, b));
        }
        else {
            fprintf(stderr, "oops idk this symbol");
            delete c;
            return NULL;
        }
        //whatever component we added, we need to make nodes a and b see that
        component* added_comp = c->get_last_component();
        a->add_component(added_comp);
        b->add_component(added_comp);
    }
    c->contains_ground_node = contains_ground_node;
    return c;
}

inline void parse_netlist(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        fprintf(stderr, "Couldn't open file oops");
        return;
    }

    std::string line;
    std::string token;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::stringstream ss(line);
      //  while (std::getline())
    }
}

#endif //NETLIST_PARSER_H

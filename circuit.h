//
// Created by Omeed on 9/3/26.
//

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "matrix.h"
#include "vector"
#include "components/component.h"
#include "components/resistor.h"
#include "unordered_map"
#include "components/node.h"

struct component_name {
    std::string name;
    int num;
    bool operator==(const component_name& other) const = default;
};

namespace std {
    template <>
    struct hash<component_name> {
        std::size_t operator()(const component_name& p) const noexcept {
            // Compute individual hash values for the struct fields
            std::size_t h1 = std::hash<std::string>{}(p.name);
            std::size_t h2 = std::hash<int>{}(p.num);

            // Combine the hashes safely using a bit-mixing formula
            // (Similar to boost::hash_combine)
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };
}

class circuit {
    //vector storing ownership of the actual components
    std::vector<std::unique_ptr<component>> comp_storage;
    std::unordered_map<int, std::unique_ptr<node_t>> node_storage;
public:
    uint8_t contains_ground_node;
    circuit();
    void add_component(std::unique_ptr<component> comp);
    void add_node(int index, std::unique_ptr<node_t> n);
    component* get_component(int index) { return comp_storage[index].get(); }
    component* get_last_component() { return comp_storage.back().get(); }
    node_t* contains_add_node(int index);

    matrix* solve_circuit();

    void print_components();

    /*void add_component(component c);
    void circuit::add_component(component c, std::string name);
    void circuit::add_component(component c, std::string name, int num);*/
};



#endif //CIRCUIT_H

//
// Created by Omeed on 9/3/26.
//

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "vector"
#include "component.h"
#include "unordered_map"

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
    std::vector<component> comp_storage;
    //unordered map storing name to component pointer
    std::unordered_map<component_name, std::unique_ptr<component>> comp_map;

public:
    circuit();
    void add_component(component c);
    void circuit::add_component(component c, std::string name);
    void circuit::add_component(component c, std::string name, int num);
};



#endif //CIRCUIT_H

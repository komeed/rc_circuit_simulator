//
// Created by Omeed on 9/3/26.
//

#include "circuit.h"

#include "components/voltage_source.h"
#include "parser/netlist_parser.h"


circuit::circuit() {
    comp_storage = std::vector<std::unique_ptr<component>>();
    node_storage = std::unordered_map<int, std::unique_ptr<node_t>>();
    contains_ground_node = 0;
}
void circuit::add_component(std::unique_ptr<component> c) {
    comp_storage.push_back(std::move(c));
}
void circuit::add_node(int index, std::unique_ptr<node_t> n) {
    node_storage[index] = (std::move(n));
}
node_t* circuit::contains_add_node(int index) {
    auto x = node_storage.find(index);
    if (x != node_storage.end()) {
        // Found,  Return the safe raw pointer from the unique_ptr
        return x->second.get();
    }
    //otherwise, create the node
    add_node(index, std::make_unique<node_t>(index));
    return node_storage[index].get();
}

matrix* circuit::solve_circuit() {
    int num_nodes = node_storage.size();
    if (contains_ground_node) {
        num_nodes --; // excluding ground
    }
    int num_vs = 0;
    for (int i = 0; i < comp_storage.size(); i++) {
        component* comp = comp_storage[i].get();
        if (comp->get_type() == COMPONENT_TYPE::VOLTAGE_SOURCE) {
            num_vs++; // for every voltage source add to mat_size (another unnknown curernt)
        }
    }
    //vs_iter = what row/col should be used for voltage source
    int vs_iter = num_nodes + 1; // + 1 because we're doing normalized (starting from 1)
    int mat_size = num_nodes + num_vs;
    matrix cond_matrix = matrix(mat_size, mat_size);
    //use malloc for current_matrix because that's also the result matrix
    matrix* current_matrix = new matrix(mat_size, 1);
    for (int i = 0; i < comp_storage.size(); i++) {
        component* comp = comp_storage[i].get();
        if (comp->get_type() == COMPONENT_TYPE::RESISTOR) {
            resistor* r = dynamic_cast<resistor*>(comp);
            int node_1 = r->node_a->id;
            int node_2 = r->node_b->id;
            if (node_1 > num_nodes || node_2 > num_nodes) {
                fprintf(stderr, "nodes are exceeded! ");
            }
            float conductance = 1.0f/(r->resistance);
            if (node_1 != GROUND_NODE_NUM) {
                cond_matrix.add_val_normal(node_1, node_1, conductance);
            }
            if (node_2 != GROUND_NODE_NUM) {
                cond_matrix.add_val_normal(node_2, node_2, conductance);
            }
            if (node_1 != GROUND_NODE_NUM && node_2 != GROUND_NODE_NUM) {
                cond_matrix.add_val_normal(node_1, node_2, -conductance);
                cond_matrix.add_val_normal(node_2, node_1, -conductance);
            }
        }
        else if (comp->get_type() == COMPONENT_TYPE::CURRENT_SOURCE) {
            current_source* cs = dynamic_cast<current_source*>(comp);
            int node_c = cs->node_a->id;
            if (node_c != GROUND_NODE_NUM) {
                current_matrix->add_val_normal(node_c, 1, cs->current);
            }
        }
        else if (comp->get_type() == COMPONENT_TYPE::VOLTAGE_SOURCE) {
            voltage_source* vs = dynamic_cast<voltage_source*>(comp);
            int node_v = vs->node_a->id;
            cond_matrix.add_val_normal(node_v, vs_iter, 1);
            cond_matrix.add_val_normal(vs_iter, node_v, 1);
            current_matrix->add_val_normal(vs_iter, 1, vs->voltage);

            vs_iter++;
        }

    }
    // to get the first component
    cond_matrix.print();
    printf("current matrix: \n");
    current_matrix->print();

    cond_matrix.solve_matrix(current_matrix);

    //go through each component and calculate voltage for each
    for (int i = 0; i < comp_storage.size(); i++) {
        component* comp = comp_storage[i].get();
        int node_a = comp->node_a->id;
        int node_b = comp->node_b->id;
        float v1, v2;
        if (node_a == GROUND_NODE_NUM) {
            v1 = 0;
        }
        else {
            v1 = current_matrix->get_val_normal(node_a, 1);
        }
        if (node_b == GROUND_NODE_NUM) {
            v2 = 0;
        }
        else {
            v2 = current_matrix->get_val_normal(node_b, 1);
        }
        comp->voltage = ABS(v1 - v2);
    }

    return current_matrix;
}

void circuit::print_components() {
    for (int i = 0; i < comp_storage.size(); i++) {
        component* comp = comp_storage[i].get();
        if (comp->get_type() == COMPONENT_TYPE::RESISTOR) {
            resistor* r = dynamic_cast<resistor*>(comp);
            printf("R: %s, Voltage: %f\n", r->id.c_str(), r->voltage);
        }
    }
}
/*
void circuit::add_component(component c) {
    comp_storage.push_back(c);
    component* comp = &comp_storage.back();

}
void circuit::add_component(component c, std::string name) {
    comp_storage.push_back(c);
}
void circuit::add_component(component c, std::string name, int num) {
    comp_storage.push_back(c);
}*/
//
// Created by Omeed on 9/6/26.
//

#include <iostream>

#include "string"
#include "../components/component.h"
#include "fstream"
#include "sstream"
#include "unordered_map"

struct SpiceComponent {
    char type;          // R, C, L, Q, M, etc.
    std::string name;   // R1, C5, etc.
    std::string node1;  // Connected node A
    std::string node2;  // Connected node B
    std::string value;  // 10k, 0.1uF, etc.
};

void generate_netlist(const std::string& filename, const std::string& gen_path ) {
    std::ifstream file(filename);
    std::string line;

    std::ofstream my_netlist(gen_path);
    if (!my_netlist) {
        fprintf(stderr, "Error: Could not open the file!");
        return;
    }

    //convert node names to node nums
    auto name_to_node_num = std::unordered_map<std::string, int>();
    int node_ind = 1; // nodes start at 1 (gnd is -1)

    while (std::getline(file, line)) {
        // Skip empty lines, comments (*), or simulation commands (.)
        if (line.empty() || line[0] == '*' || line[0] == '.') {
            continue;
        }

        std::stringstream ss(line);
        std::string name, n1, n2, val;

        // Read the standard tokens (Name, Node1, Node2, Value)
        if (ss >> name >> n1 >> n2 >> val) {
            int n1_node, n2_node;
            if (n1 == "GND") {
                n1_node = -1;
            }
            else {
                auto [it, inserted] = name_to_node_num.try_emplace(n1, node_ind);
                n1_node = it->second;
                if (inserted) {
                    node_ind++;
                    //if it's a new value, we can increase the node count
                }
            }
            if (n2 == "GND") {
                n2_node = -1;
            }
            else {
                auto [it2, inserted2] = name_to_node_num.try_emplace(n2, node_ind);
                n2_node = it2->second;
                if (inserted2) {
                    node_ind++;
                }
            }
            char type = toupper(name[0]);
            my_netlist << type << " " << name << " " << n1_node << " " << n2_node << " ";
            if (type == 'V' && val == "DC") {
                std::string actual_val;
                ss >> actual_val;
                my_netlist << actual_val;
            }
            else {
                my_netlist << val;
            }
            my_netlist << "\n";
            //now add this spice component to your own netlist file
        }
    }
    my_netlist.close();
}
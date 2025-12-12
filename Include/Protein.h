/////////////
//Protein.h//
/////////////

#pragma once
#include <string>
#include <vector>
#include <map>
#include <GLM/glm/glm.hpp>
using namespace std;

struct atom {

    float x;
    float y;
    float z;
    string element;

};

struct bond {

    int atom_one;
    int atom_two;

};

struct element_info {

    float bond_threshold;
    glm::vec3 colour;

};

class protein {

    public:
        protein() = default;
        bool load_PDB(const string &filename);

        vector<atom> atoms;
        vector<bond> bonds; 
        map<string, element_info> element_data = {

            {"H", {0.71f, glm::vec3(1.0f, 1.0f, 0.0f)}},
            {"C", {1.16f, glm::vec3(1.0f, 1.0f, 1.0f)}},
            {"N", {1.11f, glm::vec3(0.0f, 0.0f, 1.0f)}},
            {"O", {1.06f, glm::vec3(1.0f, 0.0f, 0.0f)}},
            {"P", {1.47f, glm::vec3(1.0f, 0.6f, 0.0f)}}

        };

    };

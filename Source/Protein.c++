///////////////
//Protein.c++//
///////////////

//Includes
#include "Protein.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> 
#include <cctype>
#include <string>
using namespace std;

//Functions
float atom_distance(const atom& atom_a, const atom& atom_b) {

    glm::vec3 position_a(atom_a.x, atom_a.y, atom_a.z);
    glm::vec3 position_b(atom_b.x, atom_b.y, atom_b.z);

    return glm::length(position_a - position_b);

};

//Override load_PDB method
bool protein::load_PDB(const string &filename) {
    
    ifstream file(filename);
    
    if (!file.is_open()) {

        return false;
        cout<<"Could not open file"<<endl;


    }

    cout<<"Loading file . . ."<<endl;
    

    string line;
    while (getline(file, line)){
        if (line.substr(0,4) == "ATOM" || line.substr(0,6) == "HETATM"){

            atom new_atom;

            std::string element = line.substr(76, 2);
            element.erase(std::remove_if(element.begin(), element.end(), ::isspace), element.end());

            new_atom.element = element;
            new_atom.x = stof(line.substr(30, 8));
            new_atom.y = stof(line.substr(38, 8));
            new_atom.z = stof(line.substr(46, 8));

            atoms.push_back(new_atom);


        }


    }

    if (!atoms.empty()) {
        glm::vec3 min(FLT_MAX), max(-FLT_MAX);

        for (const auto& a : atoms) {
            min.x = std::min(min.x, a.x);
            min.y = std::min(min.y, a.y);
            min.z = std::min(min.z, a.z);
            max.x = std::max(max.x, a.x);
            max.y = std::max(max.y, a.y);
            max.z = std::max(max.z, a.z);
        }

        glm::vec3 center = (min + max) * 0.5f;
        float maxExtent = std::max({max.x - min.x, max.y - min.y, max.z - min.z});
        float scale = 50.0f / maxExtent;

        for (auto& a : atoms) {
            a.x = (a.x - center.x) * scale;
            a.y = (a.y - center.y) * scale;
            a.z = (a.z - center.z) * scale;
        }
    }


    std::cout << "Loaded " << atoms.size() << " atoms"<<endl;

    
    for (int i = 0; i < atoms.size(); i++){

        for (int n = i+1; n < atoms.size(); n++){
            if (fabs(atoms[i].x - atoms[n].x) > 2.0) continue;
            if (fabs(atoms[i].y - atoms[n].y) > 2.0) continue;
            if (fabs(atoms[i].z - atoms[n].z) > 2.0) continue;

            float dist = atom_distance(atoms[i], atoms[n]);
            if (dist > 2.0) continue;
            float threshold = element_data[atoms[i].element].bond_threshold + element_data[atoms[n].element].bond_threshold;

            if (dist < threshold){

                bonds.push_back({i,n});

            }

        }

    }

    std::cout << "Loaded " << bonds.size() << " bonds"<<endl;
    std::cout<<"Loaded .pdb file";
    return true;

}
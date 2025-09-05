//////////////
//Renderer.h//
//////////////


//Includes
#pragma once
#include "Protein.h"
#include <glm.hpp>



//Classes
class renderer {
    public:
    
        void draw_protein(const protein &Protein, bool draw_bonds, bool draw_atoms, float thickness);
        

};
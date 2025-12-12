//////////////
//Renderer.h//
//////////////

#pragma once
#include "Protein.h"
#include <GLM/glm/glm.hpp>
#include <GLEW/glew-2.1.0/Include/GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

class renderer {
public:
    renderer();
    void draw_protein(const protein &Protein, bool draw_bonds, bool draw_atoms, float thickness, bool depth);
       
private:
    GLUquadric* quad;

};
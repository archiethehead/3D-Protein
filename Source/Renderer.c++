////////////////
//Renderer.c++//
////////////////

//Includes

//Standard library
#include <vector>
#include <string>
#include <iostream>

//OpenGL
#include <glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

//Renderer
#include "Renderer.h"
#include "Protein.h"

//Override draw_protein method
void renderer::draw_protein(const protein &Protein, bool draw_bonds, bool draw_atoms, float thickness) {
    
    if (draw_bonds) {
        
        glLineWidth(3.0f);
        glBegin(GL_LINES);

        for (const bond& Bond : Protein.bonds){
            
            const atom& atom_a = Protein.atoms[Bond.atom_one];
            const atom& atom_b = Protein.atoms[Bond.atom_two];

            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(atom_a.x, atom_a.y, atom_a.z);
            glVertex3f(atom_b.x, atom_b.y, atom_b.z);

        }

        glEnd();
    
    }


    if (draw_atoms) {
        
        glEnable(GL_POINT_SMOOTH);
        for (const atom& Atom : Protein.atoms) {

            glPointSize(thickness);
            glBegin(GL_POINTS);
            glm::vec3 colour = Protein.element_data.at(Atom.element).colour;
            glColor3f(colour.x, colour.y, colour.z);  
            glVertex3f(Atom.x, Atom.y, Atom.z);
            glEnd();
        }
    
    }

}
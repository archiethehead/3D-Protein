////////////////
//Renderer.c++//
////////////////

//Includes

//Standard library
#include <vector>
#include <string>
#include <iostream>

//Renderer
#include "Include/Renderer.h"
#include "Include/Protein.h"

//Override draw_protein method
renderer::renderer() {
    quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
}

void renderer::draw_protein(const protein &Protein, bool draw_bonds, bool draw_atoms, float thickness, bool depth) {
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    if (draw_bonds) {
        
        glLineWidth(2.0f);
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

        if (depth) {



            for (const atom& Atom : Protein.atoms) {

                float radius = Protein.element_data.at(Atom.element).bond_threshold * (thickness / 10);
                glm::vec3 colour = Protein.element_data.at(Atom.element).colour;
                glColor3f(colour.r, colour.g, colour.b);

                glPushMatrix();
                glTranslatef(Atom.x, Atom.y, Atom.z);
                gluSphere(quad, radius, 8, 8);
                glPopMatrix();
            }

        
        }

        else {

            glEnable(GL_POINT_SMOOTH);
            glPointSize(thickness);
            glBegin(GL_POINTS);

            for (const atom& Atom : Protein.atoms) {

                glm::vec3 colour = Protein.element_data.at(Atom.element).colour;
                glColor3f(colour.x, colour.y, colour.z);
                glVertex3f(Atom.x, Atom.y, Atom.z);
                
            }
            glEnd();
            
        }

    }

}
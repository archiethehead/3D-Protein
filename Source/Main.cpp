//////////////
//3D-Protein//
//////////////

//Standard includes
#include <iostream>
#include <vector>
#include <cmath>

//3D-Protein includes
#include <Include/Protein.h>
#include <Include/Renderer.h>

//Graphics includes
#include <GLEW/glew-2.1.0//include//GL/glew.h>
#include <Gl/GLU.h>
#include <GLFW/include/GLFW/glfw3.h>

using namespace std;

//Functions
string file_open() {

    string file_name;
    cout << "Enter .pdb file name here: ";
    cin >> file_name;

    return file_name;

}

int main() {

    bool draw_bonds = false;
    bool draw_atoms = true;
    bool depth_perspective = false;
    float thickness = 1.0f;

    bool b_just_pressed = false;
    bool m_just_pressed = false;
    bool p_just_pressed = false;

    protein new_protein;
    new_protein.load_PDB(file_open());

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    GLFWwindow* window = glfwCreateWindow(800, 600, "3D-Protein", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);

    float y_angle = 0.0, x_angle = 0.0f;
    float camera_x = 0.0, camera_y = 0.0, camera_z = -150.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    glfwSwapInterval(0);
    renderer Renderer;

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(camera_x, camera_y, camera_z);
        glRotatef(-x_angle, 1.0f, 0.0f, 0.0f);
        glRotatef(-y_angle, 0.0f, 1.0f, 0.0f);

        Renderer.draw_protein(new_protein, draw_bonds, draw_atoms, thickness, depth_perspective);
        glfwSwapBuffers(window);
        glfwPollEvents();


        //Movement controls
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera_z += 0.1f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera_z -= 0.1f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera_x += 0.1f;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera_x -= 0.1f;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera_y -= 0.1f;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera_y += 0.1f;


        //Rotational controls
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) y_angle += 0.1f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) y_angle -= 0.1f;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) x_angle -= 0.1f;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) x_angle += 0.1f;

        //Graphics controls
        bool b_pressed = glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS;
        if (b_pressed && !b_just_pressed) {

            draw_bonds = !draw_bonds;

        }
        b_just_pressed = b_pressed;

        bool m_pressed = glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS;
        if (m_pressed && !m_just_pressed) {

            draw_atoms = !draw_atoms;

        }
        m_just_pressed = m_pressed;

        bool p_pressed = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;
        if (p_pressed && !p_just_pressed) {

            depth_perspective = !depth_perspective;

        }
        p_just_pressed = p_pressed;

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);

        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) thickness = 5.0;
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) thickness = 1.0;

        //File controls
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS){

            system("cls");

            new_protein.atoms.clear();
            new_protein.bonds.clear();
            draw_bonds = false;
            draw_atoms = true;

            string file_name = file_open();
            new_protein.load_PDB(file_name);

        }

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;


}
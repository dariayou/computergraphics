#define GLEW_DLL
#define GLFW_DLL

#include <stdio.h>
#include "glew.h"
#include "glfw3.h"

int main() {

    //Initialize the library//
    if (!glfwInit()) {
        fprintf(stderr, "ERR: could not start GLFW3.\n");
        return -1;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //creating a window context//
    GLFWwindow* window = glfwCreateWindow(512, 512, "Mainwindow", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    //Initialize GLEW//
    GLenum ret = glewInit();
    if (ret != GLEW_OK) {
        fprintf(stderr, "ERR: %s\n", glewGetErrorString(ret));
        return -1;
    }

    //the main program loop//
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.4f, 1.0f, 1.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);


        glBegin(GL_QUADS); 
        glColor3f(1.0, 0.5, 1.0); 
        glVertex2f(-0.5, 0.5); 
        glVertex2f(0.5, 0.5); 
        glVertex2f(1.0, -0.5);
        glVertex2f(-1.0, -0.5); 
        glEnd();


        glfwSwapBuffers(window);


        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

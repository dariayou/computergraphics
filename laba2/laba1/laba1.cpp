#define GLEW_DLL
#define GLFW_DLL

#include <stdio.h>
#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include "Shader.h"

//Coordinates of the vertices//
float points[] = {
     0.0f,  0.0f, 0.0f,
    -0.5f, -0.0f, 0.0f,
     0.5f, -0.0f, 0.0f,
    -0.25f, 0.5f, 0.0f,
     0.25f, 0.5f, 0.0f,
};

//Vertex indices//
GLuint indices[] = {
    0, 3, 1,
    0, 4, 2,
    0, 3, 4
};


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
    GLFWwindow* window = glfwCreateWindow(512, 512, "Trapezoid", NULL, NULL);
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

    //Creating VAO, VBO, EBO//
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

 
    glBindVertexArray(VAO);

    //Filling VBO with vertex data//
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    //Filling EBO with vertex indices//
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Creating shader program//
    Shader shader("vert_shader.glsl", "frag_shader.glsl");

    //Main rendering loop//
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.4f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        float timeValue = (float)glfwGetTime();

        float red = (sin(timeValue) / 2.0f) + 0.5f;
        float green = (cos(timeValue) / 2.0f) + 0.5f;
        float blue = (sin(timeValue + 3.14f) / 2.0f) + 0.5f;

 
        shader.Use();
        shader.SetUniform("ourColor", red, green, blue, 1.0f);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

  
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

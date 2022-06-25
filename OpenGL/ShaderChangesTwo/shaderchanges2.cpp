#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "cmath"
#include "iostream"
#include "../includes/headers/shader.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float triangle1[] = {
    1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // t1r
    -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // t1l
    0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // t1t
};
float triangle2[] = {
    1.0f,  -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // t2r
    -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // t2l
    0.0f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, // t2t
};

/*
   This program will draw two triangles to the screen. This uses two seperate
   Vertex Buffer Objects and Vertex Array Objects. Our VAOs have been modified
   so that now they input 3 floats as x, y, z co-ords and 3 floats as R,G,B
   values. This allows us to give colour to each Vertice without specifying
   a Uniform variable.
*/
int main(int argc, char *argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window =
        glfwCreateWindow(800, 600, "OpenGL Triangle Test", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD\n";
        return -1;
    }
    Shader ourShader("./shader.vs", "./shader.fs");

    // VBOs -> Vertice Buffer Object
    unsigned int VBO1, VBO2;
    // VAOs -> Vertice Array Object
    unsigned int VAO1, VAO2;

    // Setup VAO and VBO for Triangle 1
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);

    // 0 -> Location 0 for input into Shader GLSL
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float), // Size of vertex data is now 6
                                             // floats as it includes RGB
                          (void *)0);
    glEnableVertexAttribArray(0);

    // 1 -> Location 1 for input into Shader GLSL
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Setup VBO and VAO for Triangle 2

    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Clear color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        // Draw triangle 1
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Draw triangle 2
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffer and poll for IO
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

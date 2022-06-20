#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <time.h>

#include "shader.hpp"
#include "input.hpp"
#include "renderer.hpp"

//TODO: implement https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites
// I'll do this don't worry about it

void initGLFW() {
    // init glfw
    glfwInit();

    // set to opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // use core profile (smaller subset of opengl features)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void onKeyGPress() {
    std::cout << "G pressed" << std::endl;
}

void onKeyGDown() {
    std::cout << "G down" << std::endl;
}

void onKeyGUp() {
    std::cout << "G up" << std::endl;
}

void a(GLFWwindow *window, int key, int scancode, int action, int mods) {
    key
}

int main() {
    initGLFW();

    // create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World!", NULL, NULL);

    if (window == NULL) {
        std::cerr << "Could not create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // load GLAD 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD failed to load." << std::endl;
        glfwTerminate();
        return -1;
    }

    // init viewport
    glViewport(0, 0, 800, 400);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load shaders
    Shader shader(
        "#version 330 core\n\nlayout (location = 0) in vec3 pos;\nlayout (location = 1) in vec3 aColor;\n\nout vec3 Color;\n\nvoid main()\n{\ngl_Position = vec4(pos, 1.0);\nColor = aColor;\n}\0",
        "#version 330 core\n\nin vec3 Color;\n\nout vec4 FragColor;\n\nvoid main()\n{\nFragColor = vec4(Color, 1.0);\n}\n\0");

    // VBO & VBA
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    }; 

    //TODO: put all below code into seperate method for organization
    unsigned int vbo, vao;

    glGenBuffers(1, &vbo); // allocate vertex buffer object
    
    glGenVertexArrays(1, &vao); // allocate vertex array object
    glBindVertexArray(vao); // bind vertex array

    // load vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind buffer
    glBindVertexArray(0); // unbind vertex array

    glfwSetKeyCallback(window, a);

    // input handler
    InputHandler input(window);

    input.registerKeyDownCallback(GLFW_KEY_G, onKeyGPress);
    input.registerKeyUpCallback(GLFW_KEY_G, onKeyGUp);
    input.registerKeyWhileDownCallback(GLFW_KEY_G, onKeyGDown);

    Renderer renderer();
    renderer.begin(GL_TRIANGLES, VERTEX_COLOR);
    
    renderer.pos(-0.5f, -0.5f, 0.0f);
    renderer.clr(1.0f, 0.0f, 0.0f);
    renderer.endVertex();

    // loop
    while (!glfwWindowShouldClose(window)) {
        input.setWindow(window);
        input.processInput();

        glClearColor(0.1f, 0.1f, 0.14f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}

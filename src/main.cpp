#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <time.h>

#include "program.hpp"
#include "shader.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "resources.hpp"

//TODO: implement systems similar to https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites
// I'll do this since I've already started work on it

#define WIDTH 800
#define HEIGHT 600

Program program;

int main()
{
    std::cout << "1" << std::endl;
    //Program *program = new Program();
    std::cout << "1asdasds" << std::endl;
    program.Init(WIDTH, HEIGHT);
    

    // input

    InputHandler input(program.currentWindow);

    // input.registerKeyDownCallback(GLFW_KEY_G, onKeyGPress);
    // input.registerKeyUpCallback(GLFW_KEY_G, onKeyGUp);
    // input.registerKeyWhileDownCallback(GLFW_KEY_G, onKeyGDown);
    
    // renderer

    // time
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // loop
    while (!glfwWindowShouldClose(program.currentWindow)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        input.setWindow(program.currentWindow);
        input.processInput();

        program.Update(deltaTime);
        program.Render();

        glfwSwapBuffers(program.currentWindow);
    }

    glfwTerminate();
    return 0;
}

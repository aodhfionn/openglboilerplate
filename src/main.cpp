#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <time.h>

#include "program.hpp"
#include "input.hpp"
#include "utils.hpp"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;
const char* NAME = "Window";

Program program;

int main()
{
    program.Init(WIDTH, HEIGHT, NAME);

    // input

    InputHandler input(program.currentWindow);

    // loop
    while (!glfwWindowShouldClose(program.currentWindow)) {
        float currentFrame;
        util::calcTime(&program.lastFrame, &program.deltaTime);

        glfwPollEvents();

        input.setWindow(program.currentWindow);
        input.processInput();

        program.Update();
        program.Render();

        glfwSwapBuffers(program.currentWindow);
    }

    glfwTerminate();
    return 0;
}

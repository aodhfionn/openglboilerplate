#include <glad/glad.h>
#include <iostream>

#include "Application.hpp"


// public
int Application::run(unsigned int width, unsigned int height, const char* windowName) {
    this->internal_initializeGLFW();
    this->currentWindow = this->internal_initializeWindow(width, height, windowName);
    this->internal_initializeGLAD();
    this->internal_initializeViewport();
    this->internal_initializeInputHandler();
    this->initialize();

    while (!glfwWindowShouldClose(this->currentWindow)) {
        glfwSwapBuffers(this->currentWindow);
        glfwPollEvents();
        
        this->inputHandler.process();
        this->render();

        this->fps = 1 / (glfwGetTime() - this->lastFrameTime);
        this->lastFrameTime = glfwGetTime();
    }
    
    this->terminate();
    this->internal_terminateGLFW();

    return this->exitCode;
}

// protected
void Application::internal_terminateGLFW() {
    glfwTerminate();
}

// private
void Application::internal_initializeGLFW() {
    if (glfwInit() == GLFW_FALSE) {
        this->exitCode = -3;
        this->terminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* Application::internal_initializeWindow(unsigned int width, unsigned int height, const char* windowName) {
    // GLFW Window
    GLFWwindow* window = glfwCreateWindow(width, height, windowName, NULL, NULL);

    if (window == NULL) {
        std::cerr << "GLFW window could not be created." << std::endl;
        this->exitCode = -1;
        this->terminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {
        glViewport(0, 0, width, height);
    });

    return window;
}

void Application::internal_initializeGLAD() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "GLAD failed to load." << std::endl;
        this->exitCode = -2;
        this->terminate();
    }
}

void Application::internal_initializeViewport() {
    int width, height;
    glfwGetWindowSize(this->currentWindow, &width, &height);
    glViewport(0, 0, width, height);
}

void Application::internal_initializeInputHandler() {
    this->inputHandler = InputHandler(this->currentWindow);
}

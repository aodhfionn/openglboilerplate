#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer.hpp"
#include "resources.hpp"

class Program
{
    public:

    unsigned int currentWidth, currentHeight;
    const char* currentName;

    float lastFrame;
    float deltaTime;

    //TODO: make width and height load from file so it saves last resolution
    // also have better way of handling resolution

    void Init(unsigned int width, unsigned int height, const char* name);
    void Clean();

    void Update();
    void Render();

    GLFWwindow* currentWindow;
    
    private:

    // Renderer renderer;
    GLFWwindow* initWindow(unsigned int width, unsigned int heigh, const char* name);
};

#endif // PROGRAM_HPP
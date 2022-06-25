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

    // make width and height load from file
    Program();

    void Init(unsigned int width, unsigned int height);
    void Clean();

    void Update(float dt);
    void Render();

    GLFWwindow* currentWindow;
    
    private:

    Renderer* renderer;
    ResourceManager* resources;
    GLFWwindow* initWindow(unsigned int width, unsigned int height);
};

#endif // PROGRAM_HPP
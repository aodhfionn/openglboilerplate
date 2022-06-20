#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Program
{
    public:

    unsigned int currentWidth, currentHeight;

    // make width and height load from file
    Program(unsigned int width, unsigned int height);

    void Init();
    void Clean();

    void Update(float dt);
    void Render();

    GLFWwindow* currentWindow;
    
    private:

    GLFWwindow* initWindow(unsigned int width, unsigned int height);
};

#endif // PROGRAM_HPP
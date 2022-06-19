#ifndef INPUT_HPP
#define INPUT_HPP

#include <glad/glad.c>
#include <iostream>

class InputHandler
{
    public:

    void setWindow();
    bool keyPressed(int key, GLFWwindow* window = currentWindow);

    void processInput();

    private:

    GLFWwindow* currentWindow;
}

#endif // INPUT_HPP
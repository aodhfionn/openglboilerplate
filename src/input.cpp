#include "input.hpp"

void InputHandler::setWindow(GLFWwindow* new) {window = new;}
bool InputHandler::keyPressed(int key, GLFWwindow* window = currentWindow) {return (glfwGetKey(window, key) == GLFW_PRESSED)}

void InputHandler::processInput(InputHandler input*)
{
    if (input->keyPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(currentWindow, true);

    
}
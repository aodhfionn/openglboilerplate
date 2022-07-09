#ifndef INPUT_HPP
#define INPUT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <functional>

#define InputActionCallbackList std::vector<std::pair<int, std::function<void()>>>

class InputHandler
{
    public:

    InputHandler(GLFWwindow* newWindow);

    void setWindow(GLFWwindow* newWindow);
    bool keyPressed(int key, GLFWwindow* window);

    void registerCallback(int key, std::function<void()> func, InputActionCallbackList*);

    void processInput();

    private:

    GLFWwindow* currentWindow;

    InputActionCallbackList keyWhileDownCallbacks;
    InputActionCallbackList keyDownCallbacks;
    InputActionCallbackList keyUpCallbacks;

    //std::function<void()> whileDownCallbacks[];
    std::vector<int> lastFrameKeysDown;
};

#endif // INPUT_HPP

#include "input.hpp"
#include "utils.hpp"

InputHandler::InputHandler(GLFWwindow* newWindow)
{
    newWindow = currentWindow;
}

void InputHandler::setWindow(GLFWwindow* newWindow) {currentWindow = newWindow;}

bool InputHandler::keyPressed(int key, GLFWwindow* window) 
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void InputHandler::processInput()
{
    std::vector<int> keysDown; // keep this vector here or it will break

    // process while down callbacks
    for (auto& element : keyWhileDownCallbacks) {
        bool downThisFrame = keyPressed(element.first, currentWindow);

        if (downThisFrame) {
            //std::cout << "check" << std::endl;
        
            element.second();
            keysDown.push_back(element.first);
        }
    }

    // process on down callbacks
    for (auto& element : keyDownCallbacks) {
        bool downLastFrame = util::vectorSearch(element.first, lastFrameKeysDown) != -1;
        bool downThisFrame = keyPressed(element.first, currentWindow);

        if (downThisFrame && downLastFrame) {
            element.second();
            keysDown.push_back(element.first);
        }
    }

    // process on up callbacks
    for (auto& element : keyUpCallbacks) {
        bool downLastFrame = util::vectorSearch(element.first, lastFrameKeysDown) != -1;
        bool downThisFrame = keyPressed(element.first, currentWindow);

        if (!downThisFrame && downLastFrame) {
            element.second();
        }
    }

    // add this frame's keys that were down
    lastFrameKeysDown = keysDown;
}

// Callback

void InputHandler::registerKeyDownCallback(int key, std::function<void()> func)
{
    std::pair<int, std::function<void()>> pair;
    pair.first = key;
    pair.second = func;

    keyDownCallbacks.push_back(pair);
}

void InputHandler::registerKeyUpCallback(int key, std::function<void()> func)
{
    std::pair<int, std::function<void()>> pair;
    pair.first = key;
    pair.second = func;

    keyUpCallbacks.push_back(pair);
}

void InputHandler::registerKeyWhileDownCallback(int key, std::function<void()> func)
{
    std::pair<int, std::function<void()>> pair;
    pair.first = key;
    pair.second = func;

    keyWhileDownCallbacks.push_back(pair);
}
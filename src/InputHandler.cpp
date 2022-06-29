#include <GLFW/glfw3.h>

#include "InputHandler.hpp"


InputHandler::InputHandler(GLFWwindow* window) {
    this->window = window;
}

InputHandler::~InputHandler() {
    this->keyDownCallbacks.clear();
    this->keyPressCallbacks.clear();
    this->keyReleaseCallbacks.clear();
}

void InputHandler::registerKeyDownCallback(int key, std::function<void()> onKeyDown) {
    this->keyDownCallbacks.push_back(std::pair<int, std::function<void()>>(key, onKeyDown));
}

void InputHandler::registerKeyPressCallback(int key, std::function<void()> onKeyPress) {
    this->keyPressCallbacks.push_back(std::pair<int, std::function<void()>>(key, onKeyPress));
}

void InputHandler::registerKeyReleaseCallback(int key, std::function<void()> onKeyRelease) {
    this->keyReleaseCallbacks.push_back(std::pair<int, std::function<void()>>(key, onKeyRelease));
}

void InputHandler::process() {
    // See comment in InputHandler.hpp
    bool current[348];

    for (std::pair<int, std::function<void()>> callback : this->keyDownCallbacks) {
        bool downNow = glfwGetKey(this->window, callback.first) == GLFW_PRESS;
        current[callback.first] = downNow;

        if (downNow) {
            current[callback.first] = true;
            callback.second();
        }
    }

    for (std::pair<int, std::function<void()>> callback : this->keyReleaseCallbacks) {
        bool downNow = glfwGetKey(this->window, callback.first) == GLFW_PRESS;
        bool downLast = this->lastCallDown[callback.first];
        current[callback.first] = downNow;

        if (!downNow && downLast) {
            callback.second();
        }
    }
    
    for (std::pair<int, std::function<void()>> callback : this->keyPressCallbacks) {
        bool downNow = glfwGetKey(this->window, callback.first) == GLFW_PRESS;
        bool downLast = this->lastCallDown[callback.first];
        current[callback.first] = downNow;

        if (downNow && !downLast) {
            callback.second();
        }
    }

    std::copy(std::begin(current), std::end(current), std::begin(this->lastCallDown));
}
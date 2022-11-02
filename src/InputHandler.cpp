#include <GLFW/glfw3.h>

#include "InputHandler.hpp"


InputHandler::InputHandler() { }

InputHandler::~InputHandler() {
    for (int i = 0; this->keyDownCallbacks->size() > i; i++) {
        this->keyDownCallbacks[i].~vector();
    }

    for (int i = 0; this->keyPressCallbacks->size() > i; i++) {
        this->keyPressCallbacks[i].~vector();
    }

    for (int i = 0; this->keyReleaseCallbacks->size() > i; i++) {
        this->keyReleaseCallbacks[i].~vector();
    }
}

void InputHandler::glfwCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS:
            for (CallbackFunc callback : this->keyPressCallbacks[key]) {
                callback();
            }
        
        case GLFW_REPEAT:
            for (CallbackFunc callback : this->keyDownCallbacks[key]) {
                callback();
            }

            break;
        
        case GLFW_RELEASE:
            for (CallbackFunc callback : this->keyReleaseCallbacks[key]) {
                callback();
            }

            break;
    }
}

/**
 * Fires for every frame while key is down
 */
void InputHandler::registerKeyDownCallback(int key, CallbackFunc onKeyDownFunc) {
    this->keyDownCallbacks[key].push_back(onKeyDownFunc);
}

/**
 * Fires once when the key is first down
 */
void InputHandler::registerKeyPressCallback(int key, CallbackFunc onKeyPressFunc) {
    this->keyPressCallbacks[key].push_back(onKeyPressFunc);
}

/**
 * Fires once when the key is first not down
 */
void InputHandler::registerKeyReleaseCallback(int key, CallbackFunc onKeyPressFunc) {
    this->keyReleaseCallbacks[key].push_back(onKeyPressFunc);
}
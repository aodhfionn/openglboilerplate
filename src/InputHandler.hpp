#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <GLFW/glfw3.h>
#include <vector>
#include <functional>

typedef std::function<void()> CallbackFunc;
typedef std::vector<CallbackFunc> CallbackFuncList;


class InputHandler {
    public:
        InputHandler();
        ~InputHandler();

        void glfwCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        /**
         * Fires for every frame while key is down
         */
        void registerKeyDownCallback(int key, CallbackFunc onKeyDown);

        /**
         * Fires once when the key is first down
         */
        void registerKeyPressCallback(int key, CallbackFunc onKeyPress);

        /**
         * Fires once when the key is first not down
         */
        void registerKeyReleaseCallback(int key, CallbackFunc onKeyRelease);
    
    private:
        GLFWwindow* window;

        CallbackFuncList keyDownCallbacks[GLFW_KEY_LAST];
        CallbackFuncList keyPressCallbacks[GLFW_KEY_LAST];
        CallbackFuncList keyReleaseCallbacks[GLFW_KEY_LAST];
};

#endif
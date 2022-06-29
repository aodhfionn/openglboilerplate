#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <GLFW/glfw3.h>
#include <functional>
#include <vector>


class InputHandler {
    public:
        InputHandler(GLFWwindow* window);
        ~InputHandler();

        void initialize();
        void process();

        /**
         * Fires for every frame while key is down
         */
        void registerKeyDownCallback(int key, std::function<void()> onKeyDown);

        /**
         * Fires once when the key is first down
         */
        void registerKeyPressCallback(int key, std::function<void()> onKeyPress);

        /**
         * Fires once when the key is first not down
         */
        void registerKeyReleaseCallback(int key, std::function<void()> onKeyRelease);
    
    private:
        GLFWwindow* window;

        std::vector<std::pair<int, std::function<void()>>> keyDownCallbacks;
        std::vector<std::pair<int, std::function<void()>>> keyPressCallbacks;
        std::vector<std::pair<int, std::function<void()>>> keyReleaseCallbacks;
        
        // 348 is the highest id for GLFW_KEY_
        // See https://www.glfw.org/docs/3.3/group__keys.html#ga9845be48a745fc232045c9ec174d8820
        // Yes, some will not be used, but will be better on CPU because lookups are fast (not vector)
        bool lastCallDown[348];
};

#endif
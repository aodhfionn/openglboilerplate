#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <GLFW/glfw3.h>

#include "InputHandler.hpp"


class Application {
    public:
        int run(unsigned int width, unsigned int height, const char* windowName);

        virtual void initialize() = 0;
        virtual void render() = 0;
        virtual void terminate() = 0;

        GLFWwindow* currentWindow;
        InputHandler inputHandler = NULL;
        
        float fps;

    private:
        int exitCode = 0;
        double lastFrameTime;

        // init
        void internal_initializeGLFW();
        GLFWwindow* internal_initializeWindow(unsigned int width, unsigned int height, const char* windowName);
        void internal_initializeGLAD();
        void internal_initializeViewport();
        void internal_initializeInputHandler();

        // term
        void internal_terminateGLFW();
};

#endif
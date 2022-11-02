#ifndef MAIN_HPP
#define MAIN_HPP

#include <glad/glad.h>

#include "Application.hpp"
#include "Program.hpp"
#include "TextRenderer.hpp"
#include "Utility.hpp"
#include "Shader.hpp"


class MyTestApplication : public Application {
    public:
        unsigned int vertexBufferingObject, vertexArrayObject, elementBufferingObject;

        void initialize();
        void render();
        void terminate();
    private:
        Program program;
        Shader vertexShader = Shader(GL_VERTEX_SHADER, true);
        Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, true);
        bool showSquare;
        TextRenderer* tr;

        void initializeProgram();
};


#endif
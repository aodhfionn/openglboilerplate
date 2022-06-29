#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

#include "Application.hpp"
#include "Program.hpp"
#include "TextRenderer.hpp"
#include "Utility.hpp"
#include "Shader.hpp"


class MyTestApplication : public Application {
    public:
        unsigned int vertexBufferingObject, vertexArrayObject, elementBufferingObject;

        void initialize() {
            this->initializeProgram();
            this->program.use();
            this->tr.initialize();

            // square
            float vertices[] = {
            //    X      Y     Z   /   R     G     B     A  / TX    TY
                 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
            };

            // render order
            unsigned int indices[] = {
                0, 1, 3,
                1, 2, 3
            };
            
            // create arrays & buffers
            glGenVertexArrays(1, &vertexArrayObject);
            glGenBuffers(1, &vertexBufferingObject);
            glGenBuffers(1, &elementBufferingObject);
            
            // bind vertex array
            glBindVertexArray(vertexArrayObject);

            // add vertices
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferingObject);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // add indices
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferingObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position: xyz
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*) 0);
            glEnableVertexAttribArray(0);
            
            // color: rgba
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*) (sizeof(float) * 3));
            glEnableVertexAttribArray(1);

            // texture: xy
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*) (sizeof(float) * 7));
            glEnableVertexAttribArray(2);

            // unbind
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            // enable blending/alpha channel
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            inputHandler.registerKeyDownCallback(GLFW_KEY_G, [this]() -> void {
                this->showSquare = true;
            });
        }

        void render() {
            glClearColor(0.1f, 0.1f, 0.14f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (this->showSquare) {
                glBindVertexArray(vertexArrayObject);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferingObject);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
            }

            this->showSquare = false;
        }

        void terminate() {
            glDeleteBuffers(1, &vertexBufferingObject);
            glDeleteBuffers(1, &elementBufferingObject);
            glDeleteVertexArrays(1, &vertexArrayObject);
        }
    private:
        Program program;
        Shader vertexShader = Shader(GL_VERTEX_SHADER, true);
        Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, true);
        bool showSquare;
        TextRenderer tr = TextRenderer("res/fonts/OpenSans-Light.ttf", 48);

        void initializeProgram() {
            loadShaderFromFile(&this->vertexShader, "res/shaders/default.vert", true);
            loadShaderFromFile(&this->fragmentShader, "res/shaders/default.frag", true);

            this->program.setVertexShader(&this->vertexShader);
            this->program.setFragmentShader(&this->fragmentShader);
            
            this->program.linkProgram();
        }
};

MyTestApplication app;

int main() {
    return app.run(1920, 1080, "Window");
}

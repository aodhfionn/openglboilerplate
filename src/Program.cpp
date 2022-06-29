#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Program.hpp"


Program::Program() {
    this->printErrors = true;
}

Program::~Program() {
    this->vertexShader->~Shader();
    this->fragmentShader->~Shader();

    if (this->isLinked) {
        glDeleteProgram(this->id);
    }
}

void Program::setVertexShader(Shader* shader) {
    this->vertexShader = shader;
}

void Program::setFragmentShader(Shader* shader) {
    this->fragmentShader = shader;
}

void Program::linkProgram() {
    if (this->isLinked) {
        throw std::runtime_error("program has already been linked!");
    }

    this->id = glCreateProgram();

    if (this->vertexShader->isCompiled) {
        glAttachShader(this->id, this->vertexShader->id);
    }

    if (this->fragmentShader->isCompiled) {
        glAttachShader(this->id, this->fragmentShader->id);
    }

    glLinkProgram(this->id);
    
    // set if program linked successfully
    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    this->isLinked = (success == GL_TRUE);

    // print linking error if there was one
    if (!this->isLinked && this->printErrors) {
        std::cerr << this->getLinkingErrors() << std::endl;
    }
}

std::string Program::getLinkingErrors() {
    if (this->isLinked) {
        return "";
    }

    char log[512];
    glGetProgramInfoLog(this->id, 512, NULL, log);
    return std::string(log);
}

void Program::use() {
    if (!this->isLinked) {
        throw std::runtime_error("program hasn't been linked!");
    }

    glUseProgram(this->id);
}

void Program::setBool(const char* name, bool val) {
    glUniform1i(glGetUniformLocation(this->id, name), (int) val);
}

#include <glad/glad.h>
#include <iostream>

#include "Shader.hpp"


Shader::Shader(int type, bool printErrors) {
    this->type = type;
    this->printErrors = printErrors;
}

Shader::~Shader() {
    if (this->isCompiled) {
        glDeleteShader(this->id);
    }
}

void Shader::setSource(const char* source) {
    this->source = source;
}

void Shader::compile() {
    // compile
    this->id = glCreateShader(this->type);
    glShaderSource(this->id, 1, &this->source, NULL);
    glCompileShader(this->id);

    // set if shader compiled successfully
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    this->isCompiled = (success == GL_TRUE);
    
    // print compiling error if there was one
    if (!this->isCompiled && this->printErrors) {
        std::cerr << this->getCompileErrors() << std::endl;
    }
}

std::string Shader::getCompileErrors() {
    if (this->isCompiled) {
        return "";
    }

    char log[512];
    glGetShaderInfoLog(id, 512, NULL, log);
    return std::string(log);
}

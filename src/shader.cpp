#include "shader.hpp"

unsigned int Shader::Compile(const char* shaderSource, int type) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &shaderSource, NULL);
    glCompileShader(id);

    return id;
}

void Shader::checkCompileErrors(unsigned int shader, bool isProgram) {
    int success;
    char infoLog[512];

    if (isProgram) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (success) {
            std::cerr << "Shader program linked successfully" << std::endl;
        } else {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "Could not link program" << std::endl << infoLog << std::endl;
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        
        if (success) {
            std::cerr << "Shader compiled successfully" << std::endl;
        } else {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "Shader failed to compile" << std::endl << infoLog << std::endl;
        }
    }
}

void Shader::loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
    // compile shaders
    vertexID = Compile(vertexShaderSource, GL_VERTEX_SHADER);
    fragmentID = Compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

    std::cout << "passed" << std::endl;
    checkCompileErrors(vertexID, false);
    checkCompileErrors(fragmentID, false);

    // create program
    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);

    checkCompileErrors(programID, true);
}

Shader::~Shader() {
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    glDeleteProgram(programID);
}

void Shader::use() {
    glUseProgram(programID);
}

void Shader::setBool(const std::string &name, bool value) const { glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value); }
void Shader::setInt(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(programID, name.c_str()), value); }
void Shader::setFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(programID, name.c_str()), value); }
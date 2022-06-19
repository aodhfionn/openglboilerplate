#include "shader.hpp"

unsigned int compileShader(const char* shaderSource, int type) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &shaderSource, NULL);
    glCompileShader(id);

    return id;
}

void checkCompileErrors(unsigned int shader, bool isProgram) {
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

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
    loadShaders(vertexShaderSource, fragmentShaderSource);
}

Shader::Shader(std::ifstream vShaderFile, std::ifstream fShaderFile) {
    std::string vertexCode;
    std::string fragmentCode;
    
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
   
    try {
        std::stringstream vShaderStream, fShaderStream;

        // write from file to streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // to string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // close
        vShaderFile.close();
        fShaderFile.close();
        
    } catch (std::ifstream::failure exception) {
        std::cerr << "Could not load shader from source file" << std::endl;
    }

    // to cstring
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    loadShaders(vShaderCode, fShaderCode);
}

void Shader::loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
    // compile shaders
    vertexID = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    fragmentID = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

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

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}
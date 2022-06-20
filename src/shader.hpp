#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
    public:

        unsigned int programID,
                     vertexID,
                     fragmentID;

        //constructor
        //Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
        //Shader(std::ifstream vertexStream, std::ifstream fragmenStream);
        ~Shader();

        void use();

        void loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
        unsigned int Compile(const char* shaderSource, int type);
    
        //TODO: use template here
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

    
        // template<typename T>
        // void setVal(const std::string &name, T value) const;
    
    private:
        void checkCompileErrors(unsigned int shader, bool isProgram);
};

#endif // SHADER_HPP
#pragma once

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
    public:
        unsigned int programID;
        unsigned int vertexID;
        unsigned int fragmentID;

        //constructor 
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void use();
    
        //TODO: use template here
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

    
        // template<typename T>
        // void setVal(const std::string &name, T value) const;
};

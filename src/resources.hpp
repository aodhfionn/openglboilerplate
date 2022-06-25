#pragma once

#include <map>

#include "shader.hpp"

class ResourceManager
{
    public:

    ResourceManager();

    Shader allocateShader(const char* vShaderFile, const char* fShaderFile, std::string name, bool fromSource);
    Shader getShader(std::string name);

    void Clear();

    private:
    
    std::map<std::string, Shader> shaderMap;

    Shader loadShaderFromSource(std::string vShaderSource, std::string fShaderSource);
    Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
};

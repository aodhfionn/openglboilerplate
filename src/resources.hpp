#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <map>

#include "shader.hpp"

class ResourceManager
{
    public:

    static Shader allocateShader(const char* vShaderFile, const char* fShaderFile, std::string name, bool fromSource);
    static Shader getShader(std::string name);

    static void Clear();

    private:

    ResourceManager();
    
    static std::map<std::string, Shader> shaderMap;

    static Shader loadShaderFromSource(std::string vShaderSource, std::string fShaderSource);
    static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
};

#endif // RESOURCES_HPP
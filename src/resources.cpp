#include "shader.hpp"
#include "resources.hpp"


std::map<std::string, Shader> ResourceManager::shaderMap;

ResourceManager::ResourceManager() {}

Shader ResourceManager::allocateShader(const char* vShader, const char* fShader, std::string name, bool fromSource)
{
    if (fromSource)
        shaderMap[name] = loadShaderFromSource((std::string)vShader, (std::string)fShader);
    else
        shaderMap[name] = loadShaderFromFile(vShader, fShader);
    
    return shaderMap[name];
}

Shader ResourceManager::getShader(std::string name) { return shaderMap[name]; }

Shader ResourceManager::loadShaderFromSource(std::string vShaderSource, std::string fShaderSource)
{
    // to cstring
    const char* vShaderCode = vShaderSource.c_str();
    const char* fShaderCode = fShaderSource.c_str();

    // instantiating and returning shader
    Shader shader;
    shader.loadShaders(vShaderCode, fShaderCode);

    return shader;
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFileName, const char* fShaderFileName)
{
    std::string vertexCode;
    std::string fragmentCode;

    try {
        std::ifstream vShaderFile(vShaderFileName);
        std::ifstream fShaderFile(fShaderFileName);
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

    return loadShaderFromSource(vertexCode, fragmentCode);
}

void ResourceManager::Clear()
{
    for (auto& element : shaderMap)
        glDeleteProgram(element.second.programID);
}
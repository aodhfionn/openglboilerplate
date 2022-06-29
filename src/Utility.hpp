#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.hpp"


std::string readFileAsString(std::string fileName) {
    std::string fileContents;

    try {
        std::ifstream inputFileStream(fileName);
        std::stringstream stringStream;

        stringStream << inputFileStream.rdbuf();
        fileContents = stringStream.str();

        inputFileStream.close();
    } catch (std::ifstream::failure exception) {
        std::cerr << "Couldn't read file: " << fileName << std::endl;
    }

    return fileContents;
}

void loadShaderFromFile(Shader *shader, std::string filePath, bool compile) {
    std::string s = readFileAsString(filePath);
    shader->setSource(s.c_str());
    if (compile) shader->compile();
}

#endif
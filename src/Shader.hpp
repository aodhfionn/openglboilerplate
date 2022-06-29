#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>


class Shader {
    public:
        bool isCompiled;
        bool printErrors;
        int type;
        const char* source;
        unsigned int id;


        Shader(int type, bool printErrors);
        ~Shader();

        void setSource(const char* source);
        void compile();

        std::string getCompileErrors();

        void setBool(const char* name, bool val);
};

#endif
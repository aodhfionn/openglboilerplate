#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Shader.hpp"


class Program {
    public:
        // fields
        Shader* vertexShader;
        Shader* fragmentShader;
        unsigned int id;
        bool isLinked;

        // methods
        Program();
        ~Program();

        void setVertexShader(Shader* shader);
        void setFragmentShader(Shader* shader);
        void linkProgram();

        std::string getLinkingErrors();

        void use();

        void setBool(const char* name, bool val);
        void setInt(const char* name, int val);
        void setFloat(const char* name, float val);
        void setDouble(const char* name, double val);
    private:
        bool printErrors;
};

#endif // PROGRAM_HPP
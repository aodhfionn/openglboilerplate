#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <iostream>

class Program
{
    public:

    unsigned int width, height;

    // make width and height load from file
    Program(unsigned int width, unsigned int height);

    void Init();

    void Update(float dt);
    void Render();
};

#endif // PROGRAM_HPP
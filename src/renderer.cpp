#include <iostream>
#include "renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void temp(std::vector<float> a) {
    std::cout << "[";
    for (int i = 0; i < a.size(); i++) {
        std::cout << a.at(i) << "f, ";
    }
    std::cout << "]" << std::endl;
}

void temp(float a[]) {
    std::cout << "[";
    for (int i = 0; i < sizeof(a); i++) {
        std::cout << a[i] << "f, ";
    }
    std::cout << "]" << std::endl;
}

std::vector<float> tempVertexBuffer;
std::vector<float> vertexBuffer;
std::vector<float> indicesBuffer;

unsigned int vbo, vao;

BatchRenderer::BatchRenderer()
{
    
}

BatchRenderer::~BatchRenderer()
{
    vertexBuffer.clear();
    indicesBuffer.clear();

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void BatchRenderer::initialize()
{
    this->initVertexAttribPointers();
    this->createGLBuffers();
}

BatchRenderer BatchRenderer::newElement()
{
    tempVertexBuffer.clear();
    this->expectingNext = BatchRendererNext::POSITION;

    return *this;
}

BatchRenderer BatchRenderer::pos(float x, float y, float z)
{
    if (this->expectingNext != POSITION) {
        throw std::invalid_argument("wrong order, not expecting a position right now");
    }

    tempVertexBuffer.push_back(x);
    tempVertexBuffer.push_back(y);
    tempVertexBuffer.push_back(z);

    this->expectingNext = BatchRendererNext::COLOR;

    return *this;
}

BatchRenderer BatchRenderer::clr(float r, float g, float b, float a)
{
    if (this->expectingNext != COLOR) {
        throw std::invalid_argument("wrong order, not expecting a color right now");
    }

    tempVertexBuffer.push_back(r);
    tempVertexBuffer.push_back(g);
    tempVertexBuffer.push_back(b);

    //tempVertexBuffer.push_back(a);

    this->expectingNext = BatchRendererNext::POSITION;

    return *this;
}

BatchRenderer BatchRenderer::nextVertex()
{
    temp(tempVertexBuffer);

    if (this->expectingNext != POSITION) {
        throw std::invalid_argument("malformed");
    }

    return *this;
}

void BatchRenderer::finishElement()
{
    // std::cout<<"Temp: ";
    temp(tempVertexBuffer);

    for (float f : tempVertexBuffer) {
        vertexBuffer.push_back(f);
    }
}

void BatchRenderer::batch()
{
    // float vertices[this->vertexBuffer.size()];
    // std::copy(this->vertexBuffer.begin(), this->vertexBuffer.end(), vertices);

    // // std::cout << "adfjisoa: ";
    // temp(vertices);

    float vertices[18] {
        // x     y     z    r      g     b
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    // bind
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // draw
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    this->initVertexAttribPointers();

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vertexBuffer.clear();
}

void BatchRenderer::initVertexAttribPointers()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);
}

void BatchRenderer::createGLBuffers()
{
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
}
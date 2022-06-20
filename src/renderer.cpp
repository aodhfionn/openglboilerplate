#include "renderer.hpp"

void Renderer::begin(int mode, RendererMode renderMode)
{
    this->mode = mode;
    this->format = format;
}

void Renderer::pos(float x, float y, float z)
{
    vertexBuffer.push_back(x);
    vertexBuffer.push_back(y);
    vertexBuffer.push_back(z);
}

void Renderer::clr(float r, float g, float b, float a)
{
    vertexBuffer.push_back(r);
    vertexBuffer.push_back(g);
    vertexBuffer.push_back(b);
    vertexBuffer.push_back(a);
}

void Renderer::endVertex() {
    
}
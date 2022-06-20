#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <vector>

class Renderer
{
    public:
        RenderVertex *current;

        Renderer();

        void begin(int mode);
        Renderer* pos(float x, float y, float z);
        Renderer* clr(float r, float g, float b, float a);
        void endVertex();
        void render();

    private:
        int mode;
};

class RenderVertex {
    public:
        unsigned int vbo, vao;
        int type;

        RenderVertex(int type);
        ~RenderVertex();

        void render();
        std::vector<float> vertexBuffer;
};

#endif
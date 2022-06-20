#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <vector>

enum RendererMode
{
    XYZ,
    XYZ_RGBA
};

class Renderer
{
    public:
        void begin(int mode, RendererMode renderMode);
        void pos(float x, float y, float z);
        void clr(float r, float g, float b, float a);
        void endVertex();
        void draw();

    private:
        int mode;
        RendererMode format;
        std::vector<float> vertexBuffer;
        std::vector<float> buffer;
};

#endif
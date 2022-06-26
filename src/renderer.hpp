#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#include <vector>


enum BatchRendererNext {
    POSITION,
    COLOR
};

class BatchRenderer {
    public:
    
    BatchRenderer();
    ~BatchRenderer();

    void initialize();

    BatchRenderer newElement();
    BatchRenderer pos(float x, float y, float z);
    BatchRenderer clr(float r, float g, float b, float a);
    BatchRenderer nextVertex();
    void finishElement();

    void batch();

    private:

    void initVertexAttribPointers();
    void createGLBuffers();

    BatchRendererNext expectingNext;
};

class TextRenderer {
    public:

    TextRenderer(BatchRenderer *renderer, std::string fontFile, int fontSize);
    ~TextRenderer();

    void initializeFont();

    void render(std::string string, float x, float y, float r, float g, float b, float a);

    float getStringWidth(std::string string);
    float getStringHeight(std::string string);

    private:

    BatchRenderer *renderer;
};

#endif // RENDERER_HPP
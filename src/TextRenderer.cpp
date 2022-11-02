/**
 * [!] See header file for important comments. 
 */

#include "TextRenderer.hpp"

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_LCD_FILTER_H


TextRenderer::TextRenderer(GLFWwindow* window) {
    if (FT_Init_FreeType(&this->library)) {
        throw std::runtime_error("could not initialize FreeType");
    }

    if (FT_Library_SetLcdFilter(this->library, FT_LCD_FILTER_DEFAULT)) {
        throw std::runtime_error("could not apply lcd filter");
    }

    this->window = window;
}

TextRenderer::~TextRenderer() {
    FT_Done_Face(this->face);
    FT_Done_FreeType(this->library);
}

void TextRenderer::createDynamicBuffer() {
    // create arrays & buffers
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    
    // bind vertex array
    glBindVertexArray(this->vao);

    // add vertices
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * 6, NULL, GL_DYNAMIC_DRAW);

    // position: xyz
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*) 0);
    glEnableVertexAttribArray(0);
    
    // color: rgba
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*) (sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // texture: xy
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*) (sizeof(float) * 7));
    glEnableVertexAttribArray(2);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::initializeTextures() {
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // when downscaling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // when upscaling

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::initializeFontFace(const char* fontFilePath) {
    if (FT_New_Face(this->library, fontFilePath, 0, &this->face)) {
        throw std::runtime_error("could not create font face");
    }
}

void TextRenderer::loadFont(const char* fontFilePath) {
    this->initializeFontFace(fontFilePath);
    this->createDynamicBuffer();
    this->initializeTextures();
}

Dimensions TextRenderer::renderCharacter(Application* app, const char c, float x, float y, unsigned int fontSize) {
    float wwF = (float) app->windowWidth;
    float whF = (float) app->windowHeight;

    if (c == ' ') {
        return {
            fontSize / wwF,
            0.f
        };
    }

    if (FT_Set_Char_Size(this->face, 0, fontSize * 64, 250, 0)) {
        throw std::runtime_error("could not set font character size");
    }

    if (FT_Load_Char(this->face, c, FT_LOAD_RENDER)) {
        throw std::runtime_error("could not render character");
    }

    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        this->face->glyph->bitmap.width,
        this->face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        this->face->glyph->bitmap.buffer
    );

    float width = ((float) this->face->glyph->bitmap.width) / wwF;
    float height = ((float) this->face->glyph->bitmap.rows) / whF;

    glBindVertexArray(this->vao);

    y -= (((int) this->face->glyph->bitmap.rows) - ((int) this->face->glyph->bitmap_top)) / whF;

    float vertices[] = {
         x,         y + height, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         x + width, y + height, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         x,         y,          0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,

         x,         y,          0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
         x + width, y,          0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         x + width, y + height, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
    };

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);    

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return {
        width,
        height
    };
}

Dimensions TextRenderer::renderString(Application* app, std::string str, float x, float y, unsigned int fontSize, float gap) {
    float cx = x;
    float height = 0.f;

    for (char c : str) {
        Dimensions d = this->renderCharacter(app, c, cx, y, fontSize);
        cx += d.width + ((float) gap / (float) app->windowWidth / (float) fontSize);
        height = (d.height > height ? d.height : height);
    }

    return {
        cx,
        height
    };
}

Dimensions TextRenderer::renderLines(Application* app, std::string str[], size_t strCount, float x, float y, unsigned int fontSize, float gap) {
    Dimensions d;
    float start = y;

    for (int i = 0; strCount > i; i++) {
        Dimensions d2 = this->renderString(app, str[i], x, y, fontSize, gap);
        y -= d2.height;

        d.width = (d2.width > d.width ? d2.width : d.width);
        d.height += (d2.height > d.height ? d2.height : d.height);
    }

    return d;
}

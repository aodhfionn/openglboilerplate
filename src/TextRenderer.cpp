#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "TextRenderer.hpp"


TextRenderer::TextRenderer(std::string fontFile, int fontSize) {
    this->fontFile = fontFile;
    this->fontSize = fontSize;
}

TextRenderer::~TextRenderer() {
    for (Glyph g : this->glyphs) {
        Texture t = *g.pTexture;
        t.~Texture();
    }
}

int TextRenderer::getFontSize() {
    return this->fontSize;
}

void TextRenderer::initialize() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("could not initialize FreeType");
    }

    // std::string fontName = FileSystem::getPath(this->fontFile);
    if (FT_New_Face(ft, this->fontFile.c_str(), 0, &this->fontFace)) {
        throw std::runtime_error("could not create font face");
    }

    FT_Set_Pixel_Sizes(fontFace, 0, this->fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (int i = 0; CHARS_TO_INIT > i; i++) {
        try {
            this->initializeChar((char) i);
        } catch (std::runtime_error err) {
            continue;
        }
    }

    FT_Done_Face(this->fontFace);
    FT_Done_FreeType(ft);
}

void TextRenderer::initializeChar(char c) {
    if (FT_Load_Char(this->fontFace, c, FT_LOAD_RENDER)) {
        throw std::runtime_error("couldn't load character: " + std::string(1, c));
    }

    Glyph g = Glyph();
    Texture texture = Texture(GL_TEXTURE_2D, GL_RED, GL_UNSIGNED_INT);

    g.width = this->fontFace->glyph->bitmap.width;
    g.height = this->fontFace->glyph->bitmap.rows;
    g.bearingX = this->fontFace->glyph->bitmap_left;
    g.bearingY = this->fontFace->glyph->bitmap_top;

    texture.width = g.width;
    texture.height = g.height;
    texture.pixelData = this->fontFace->glyph->bitmap.buffer;
    texture.create();
    
    g.pTexture = &texture;

    this->glyphs[c] = g;
}

unsigned int TextRenderer::render(std::string str, float x, float y, float z) {
    unsigned int rx = 0;

    for (char c : str) {
        rx += this->render(c, x + rx, y, z);
    }

    return rx;
}

unsigned int TextRenderer::render(char c, float x, float y, float z) {
    Glyph g = this->glyphs[c];

    

    return g.width;
}

unsigned int TextRenderer::getRenderHeight(std::string str) {
    unsigned int max;

    for (char c : str) {
        unsigned int height = this->glyphs[c].height;
        
        if (height > max) {
            max = height;
        }
    }

    return max;
}

unsigned int TextRenderer::getRenderWidth(std::string str) {
    unsigned int width;

    for (char c : str) {
        width += this->glyphs[c].width;
    }

    return width;
}
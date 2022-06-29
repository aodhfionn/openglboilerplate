#ifndef TEXTRENDERER_HPP
#define TEXTRENDERER_HPP

#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Texture.hpp"

#define CHARS_TO_INIT 128


struct Glyph {
    Texture *pTexture;
    unsigned int width, height;
    unsigned int bearingX, bearingY;
};

class TextRenderer {
    public:
        TextRenderer(std::string fontFile, int fontSize);
        ~TextRenderer();

        int getFontSize();

        void initialize();

        unsigned int render(std::string str, float x, float y, float z);
        unsigned int render(char c, float x, float y, float z);

        unsigned int getRenderHeight(std::string str);
        unsigned int getRenderWidth(std::string str);

    private:
        int fontSize;
        std::string fontFile;
        FT_Face fontFace;
        Glyph glyphs[CHARS_TO_INIT];

        void initializeChar(char c);
};

#endif
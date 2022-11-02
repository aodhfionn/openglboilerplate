/**
 * A Text Renderer
 * 
 * What's done:
 * - Rendering text
 * 
 * What needs to be done:
 * - Kerning (https://en.wikipedia.org/wiki/Kerning)
 * - Ligatures (https://en.wikipedia.org/wiki/Ligature_(writing))
 * - Bidirectional text transforming (BIDI) (https://unicode.org/reports/tr9/)
 * - LCD Subpixel rendering (https://github.com/mrandri19/freetype-opengl-experiments#screenshots)
 * - Emoji rendering (https://github.com/mrandri19/freetype-opengl-experiments/blob/master/docs/first_working_emoji.png)
 * - Antialiasing
 * - Font character pre-rendering & cache
 * - Transparent texture backgrounds for rendered characters
 * 
 */

#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <GLFW/glfw3.h>

#include <string>
#include "Application.hpp"


struct Dimensions {
    float width;
    float height;
};

class TextRenderer {
    public:
        GLFWwindow* window;
        FT_Library library;
        FT_Face face;
        unsigned int textureId;
        unsigned int vao;
        unsigned int vbo;

        TextRenderer(GLFWwindow* window);
        ~TextRenderer();

        void loadFont(const char* fontFilePath);
        Dimensions renderCharacter(Application* app, const char c, float x, float y, unsigned int fontSize);
        Dimensions renderString(Application* app, std::string str, float x, float y, unsigned int fontSize, float spaceWidth = 24.0f);
        Dimensions renderLines(Application* app, std::string str[], size_t strCount, float x, float y, unsigned int fontSize, float gap);
    
    private:
        void initializeFontFace(const char* fontFilePath);
        void createDynamicBuffer();
        void initializeTextures();
};

#endif
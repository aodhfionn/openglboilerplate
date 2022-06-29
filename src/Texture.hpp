#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>


class Texture {
    public:
        // fields
        unsigned int id;

        GLenum target;
        GLint format;
        GLenum type;

        unsigned int width, height;
        const void* pixelData;

        // methods
        Texture(GLenum target, GLint format, GLenum type);
        ~Texture();

        void create();

        void use();
};


#endif
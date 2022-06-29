#include "Texture.hpp"

Texture::Texture(GLenum target, GLint format, GLenum type) {
    this->target = target;
    this->format = format;
    this->type = type;
}

Texture::~Texture() {
    glDeleteTextures(1, &this->id);
}

void Texture::create() {
    glGenTextures(1, &this->id);
    this->use();
    
    switch (this->target) {
        case GL_TEXTURE_2D:
            glTexImage2D(
                this->target,
                0,
                this->format,
                this->width,
                this->height,
                0,
                this->format,
                this->type,
                this->pixelData
            );
    }
}

void Texture::use() {
    glBindTexture(this->target, this->id);
    // glActiveTexture()
}
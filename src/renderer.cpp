// #include <iostream>
// #include <glad/glad.h>
// #include "renderer.hpp"

// Renderer::Renderer()
// {
//     // position :: xyz
//     std::cout << "sfgsdfg";
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*) 0);
//     std::cout << "g9f";
//     glEnableVertexAttribArray(0);

//     // color :: rgba
//     std::cout << "d9fk";
//     glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*) (sizeof(float) * 3));
//     std::cout << "alks";
//     glEnableVertexAttribArray(1);
// }

// void Renderer::begin(int mode)
// {
//     this->mode = mode;
//     this->current = new RenderVertex(mode);
// }

// Renderer* Renderer::pos(float x, float y, float z)
// {
//     this->current->vertexBuffer.push_back(x);
//     this->current->vertexBuffer.push_back(y);
//     this->current->vertexBuffer.push_back(z);

//     return this;
// }

// Renderer* Renderer::clr(float r, float g, float b, float a)
// {
//     this->current->vertexBuffer.push_back(r);
//     this->current->vertexBuffer.push_back(g);
//     this->current->vertexBuffer.push_back(b);
//     this->current->vertexBuffer.push_back(a);

//     return this;
// }

// void Renderer::endVertex()
// {
//     if (this->current->vertexBuffer.size() % 7 == 0) {
//         // TODO: make this error message better
//         throw std::length_error("vertex does not have enoguh values (are you mising position or color?)");
//     }

//     float* vertices = this->current->vertexBuffer.data();

//     // allocate
//     glGenBuffers(1, &this->current->vbo);
//     glGenVertexArrays(1, &this->current->vao);

//     // bind
//     glBindBuffer(GL_ARRAY_BUFFER, this->current->vbo);
//     glBindVertexArray(this->current->vao);

//     // data
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     // unbind
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     glBindVertexArray(0);
// }

// void Renderer::render()
// {
//     this->current->render();
// }


// // render vertex
// RenderVertex::RenderVertex(int type)
// {
//     this->type = type;
// }

// RenderVertex::~RenderVertex()
// {
//     glDeleteBuffers(1, &this->vbo);
//     glDeleteVertexArrays(1, &this->vao);
// }

// void RenderVertex::render()
// {
//     glBindVertexArray(this->vao);
//     glDrawArrays(this->type, 0, this->vertexBuffer.size());
// }
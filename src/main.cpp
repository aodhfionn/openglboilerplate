#include "main.hpp"

#include <iostream>
#include <vector>


void MyTestApplication::initialize() {
    this->initializeProgram();
    this->program.use();

    this->tr = new TextRenderer(this->currentWindow);
    this->tr->loadFont("res/fonts/OpenSans/static/OpenSans/OpenSans-Regular.ttf");

    // square
    /*float vertices[] = {
    //    X      Y     Z   /   R     G     B     A  / TX    TY
         0.2f,  0.2f, 0.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f
    };

    // render order
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    // create arrays & buffers
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferingObject);
    glGenBuffers(1, &elementBufferingObject);
    
    // bind vertex array
    glBindVertexArray(vertexArrayObject);

    // add vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferingObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // add indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferingObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Application::inputHandler.registerKeyPressCallback(GLFW_KEY_G, [this]() -> void {
        this->showSquare = true;
    });

    Application::inputHandler.registerKeyReleaseCallback(GLFW_KEY_G, [this]() -> void {
        this->showSquare = false;
    });*/
}

void MyTestApplication::render() {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    std::wifstream is("sample.txt");
    std::wstring buf;
    std::vector<std::wstring> strs;

    while (std::getline(is, buf)) {
        strs.push_back(buf);
    }

    std::wstring* sarr = &strs[0];

    this->tr->renderLines(this, sarr, strs.size(), -1.f, 0.5f, 50);

    this->tr->renderString(this, L"NO WAY ❤️✌️😀😬😁😂😃😄😅😆💀", -0.5f, 0.5f, 50);
}

void MyTestApplication::terminate() {
    Application::terminate();

    glDeleteBuffers(1, &vertexBufferingObject);
    glDeleteBuffers(1, &elementBufferingObject);
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void MyTestApplication::initializeProgram() {
    loadShaderFromFile(&this->vertexShader, "res/shaders/default.vert", true);
    loadShaderFromFile(&this->fragmentShader, "res/shaders/default.frag", true);

    this->program.setVertexShader(&this->vertexShader);
    this->program.setFragmentShader(&this->fragmentShader);

    this->program.linkProgram();
}

int main() {
    MyTestApplication app;

    return app.run(1920, 1080, "Window");
}

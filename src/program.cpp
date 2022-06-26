#include "program.hpp"
#include "input.hpp"
#include "renderer.hpp"

// static
BatchRenderer renderer;

void onResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* Program::initWindow(unsigned int width, unsigned height, const char* name)
{
    GLFWwindow* newWindow = glfwCreateWindow(width, height, name, NULL, NULL);

    if (newWindow == NULL) {
        std::cerr << "Could not create GLFW window." << std::endl;
        this->Clean();
    }

    glfwMakeContextCurrent(newWindow);

    return newWindow;
}

void debug()
{
    static unsigned int i = 0;

    std::cout << i << std::endl;

    i++;
}

void Program::Init(unsigned int width, unsigned int height, const char* name)
{
    debug();
    // init glfw
    glfwInit();

    // set to opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // use core profile (smaller subset of opengl features)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    debug();
    currentWidth = width;
    currentHeight = height;
    currentName = name;
    
    debug();

    debug();

    currentWindow = initWindow(currentWidth, currentHeight, name);

    // load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD failed to load." << std::endl;
        this->Clean();
    }

    // set resize event handler
    glfwSetFramebufferSizeCallback(currentWindow, onResize);
    glViewport(0, 0, 800, 400);

    renderer.initialize();
}

void Program::Update()
{
    
}

void Program::Render()
{
    glClearColor(0.1f, 0.1f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // for (int i = 0; i <= 4; i++)
    // {
    //     renderer.newElement()
    //     .pos(0.0f, 1.0f, 0.0f).clr(1.0f, 0.0f, 0.0f, 1.0f).nextVertex()
    //     .pos(1.0f, 1.0f, 0.0f).clr(0.0f, 1.0f, 0.0f, 1.0f).nextVertex()
    //     .pos(1.0f, 0.0f, 0.0f).clr(0.0f, 0.0f, 1.0f, 1.0f).nextVertex()
    //     .pos(0.0f, 0.0f, 0.0f).clr(0.0f, 0.0f, 0.0f, 1.0f).finishElement();
    // }

    // renderer.newElement();

    // renderer.pos(-0.5f, -0.5f, 0.0f);
    // renderer.clr(1.0f, 0.0f, 0.0f, 1.0f);
    // renderer.nextVertex();

    // renderer.pos(0.5f, -0.5f, 0.0f);
    // renderer.clr(0.0f, 1.0f, 0.0f, 1.0f);
    // renderer.nextVertex();

    // renderer.pos(0.0f, 0.5f, 0.0f);
    // renderer.clr(0.0f, 0.0f, 1.0f, 1.0f);
    // renderer.nextVertex();
    
    // renderer.finishElement();
    
    renderer.batch();
}

void Program::Clean()
{
    ResourceManager::Clear();
    glfwTerminate();
}
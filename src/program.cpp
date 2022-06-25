#include "program.hpp"
#include "renderer.hpp"
#include "resources.hpp"
#include "input.hpp"


// static
void onResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void onKeyGPress()
{
    std::cout << "G pressed" << std::endl;
}

void onKeyGDown()
{
    std::cout << "G down" << std::endl;
}

void onKeyGUp()
{
    std::cout << "G up" << std::endl;
}

// program
Program::Program()
{
    
}

GLFWwindow* Program::initWindow(unsigned int width, unsigned height)
{
    GLFWwindow* newWindow = glfwCreateWindow(800, 600, "Hello World!", NULL, NULL);

    if (newWindow == NULL) {
        std::cerr << "Could not create GLFW window." << std::endl;
        this->Clean();
    }

    glfwMakeContextCurrent(newWindow);

    return newWindow;
}


void Program::Init(unsigned int width, unsigned int height)
{
    // init glfw
    glfwInit();

    // set to opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // use core profile (smaller subset of opengl features)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    currentWidth = width;
    currentHeight = height;

    std::cout << "56" << std::endl;
    resources = new ResourceManager();
    std::cout << "35" << std::endl;
    renderer = new Renderer();
    std::cout << "545" << std::endl;

    std::cout << "a" << std::endl;
    Shader shader = resources->allocateShader("shaders/default.vert", "shaders/default.frag", "main", false);

    std::cout << "b" << std::endl;
    GLFWwindow* currentWindow = initWindow(currentWidth, currentHeight);

    // load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD failed to load." << std::endl;
        this->Clean();
    }

    // set resize event handler
    glfwSetFramebufferSizeCallback(currentWindow, onResize);
    glViewport(0, 0, 800, 400);
}

void Program::Update(float dt)
{
    
}

void Program::Render()
{
    glClearColor(0.1f, 0.1f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->begin(GL_TRIANGLES);
    renderer->pos(0.0f, 1.0f, 0.0f)->clr(1.0f, 0.0f, 0.0f, 0.0f)->endVertex();
    renderer->pos(0.0f, 0.0f, 0.0f)->clr(0.0f, 1.0f, 0.0f, 0.0f)->endVertex();
    renderer->pos(1.0f, 0.0f, 0.0f)->clr(0.0f, 0.0f, 1.0f, 0.0f)->endVertex();
    renderer->render();
    renderer->current->~RenderVertex();
}

void Program::Clean()
{
    resources->Clear();
    glfwTerminate();
}
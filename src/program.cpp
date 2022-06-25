#include "program.hpp"
#include "input.hpp"


// static
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

void Program::Init(unsigned int width, unsigned int height, const char* name)
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
    currentName = name;

    renderer = new Renderer();

    Shader shader = ResourceManager::allocateShader("shaders/default.vert", "shaders/default.frag", "main", false);

    GLFWwindow* currentWindow = initWindow(currentWidth, currentHeight, name);

    // load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD failed to load." << std::endl;
        this->Clean();
    }

    // set resize event handler
    glfwSetFramebufferSizeCallback(currentWindow, onResize);
    glViewport(0, 0, 800, 400);
}

void Program::Update()
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
    ResourceManager::Clear();
    glfwTerminate();
}
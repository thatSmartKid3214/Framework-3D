#include <platform/window.h>
#include <glad/glad.h>

void initGL()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

Window::Window(std::string name, int width, int height)
{
    initGL();

    this->name = name;
    this->width = width;
    this->height = height;

    window = SDL_CreateWindow(name.c_str(), width, height, SDL_WINDOW_OPENGL);

    if(!window)
    {
        std::cout << "Window Creation failed!" << std::endl;
        return;
    }

    ctx = SDL_GL_CreateContext(window);
}

SDL_Window* Window::getWindow()
{
    return window;
}

bool Window::isOpen()
{
    return window != NULL;
}


void Window::clearColor(float red, float green, float blue)
{
    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::update()
{
    SDL_GL_SwapWindow(window);
}

void Window::updateViewport(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::destroyWindow()
{
    SDL_GL_DestroyContext(ctx);
    SDL_DestroyWindow(window);

    window = NULL;
}
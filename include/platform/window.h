#ifndef GL_WINDOW_H
#define GL_WINDOW_H


#include <iostream>
#include <SDL3/SDL.H>


void initGL();

class Window
{
private:
    SDL_Window* window;
    SDL_GLContext ctx;

public:
    std::string name;
    int width;
    int height;

    Window(std::string name, int width, int height);

    SDL_Window* getWindow();
    bool isOpen();

    void clearColor(float red, float green, float blue);
    void update();
    void updateViewport(int width, int height);
    void destroyWindow();

};



#endif
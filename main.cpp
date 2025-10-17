#include <framework.h>

float triangle[15] = {
    0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f,  // top left
    0.8f, -0.5f, 0.0f,
};
int indices[] = {
    0, 3, 2,
    0, 1, 4
};

int main()
{
    bool result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if(!result) 
    {
        std::cout << "Failed to initialize SDL3" << std::endl;
        return -1;
    } 

    Window win = Window("Engine 3D", 900, 600);
    if(!win.isOpen()) return -1;
    if(!initGLAD()) return -1;
    win.updateViewport(win.width, win.height);

    bool running = true;
    SDL_Event event;

    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;
    VAO.bind();
    VBO.bind();
    EBO.bind();
    VBO.addFloatData(triangle, sizeof(triangle), GL_STATIC_DRAW);
    VBO.setAttribute(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    EBO.addData(indices, sizeof(indices), GL_STATIC_DRAW);
    VBO.enableAttribute(0);
    VBO.unbind();
    VAO.unbind();

    ShaderProgram program("shaders/vert.glsl", "shaders/frag.glsl");
    program.use();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (running)
    {
        win.clearColor(0.7f, 0.35f, 0.35f);

        VAO.bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                running = false;
                break;
            }
        }


        win.update();
    }

    win.destroyWindow();

    SDL_Quit();

    return 0;
}
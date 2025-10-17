#include <iostream>
#include <fstream>


#include <glad/glad.h>
#include <SDL3/SDL.h>

float triangle[12] = {
    0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f  // top left
};
int indices[] = {
    0, 1, 2,
    2, 3, 0
};


bool initGLAD()
{
    bool result = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    if(!result) {
        std::cout << "Failed to initialize GLAD!" << std::endl;
    }

    return result;
}

void getShaderStatus(unsigned int shader, int size, char* log)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, size, NULL, log);
        std::cout << "Shader Compilation failed! Error: " << log << std::endl;
    }
}

void getProgramStatus(unsigned int program, int size, char* log)
{
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, size, NULL, log);
        std::cout << "Program Link Error: " << log << std::endl;
    }
}


int main()
{
    bool result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    if(!result) 
    {
        std::cout << "Failed to initialize SDL3" << std::endl;
        return -1;
    } 

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* win = SDL_CreateWindow("Engine 3D", 900, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context = SDL_GL_CreateContext(win);

    if (win == NULL) {
	    std::cout << "Failed to create a window! Error: " << SDL_GetError() << std::endl;
        return -1;
    }  

    if(!initGLAD()) return -1;

    bool running = true;
    SDL_Event event;

    glViewport(0, 0, 900, 600);

    unsigned int vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    const char* shaderCode = NULL;
    std::string vertShader = "";
    std::string fragShader = "";

    std::string line;
    std::ifstream file("shaders/vert.glsl");
    while(std::getline(file, line))
    {
        vertShader += line + "\n";
    }
    file.close();
    file.open("shaders/frag.glsl");
    while(std::getline(file, line))
    {
        fragShader += line + "\n";
    }
    file.close();

    shaderCode = vertShader.c_str();

    unsigned int vertShaderID;
    vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShaderID, 1, &shaderCode, NULL);
    glCompileShader(vertShaderID);

    unsigned int fragShaderID;
    shaderCode = fragShader.c_str();
    fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderID, 1, &shaderCode, NULL);
    glCompileShader(fragShaderID);

    char* log = new char[512];
    getShaderStatus(vertShaderID, 512, log);
    getShaderStatus(fragShaderID, 512, log);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShaderID);
    glAttachShader(shaderProgram, fragShaderID);

    glLinkProgram(shaderProgram);
    getProgramStatus(shaderProgram, 512, log);

    glDeleteShader(vertShaderID);
    glDeleteShader(fragShaderID);

    delete log;

    glUseProgram(shaderProgram);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (running)
    {
        glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
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


        SDL_GL_SwapWindow(win);
    }

    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    SDL_DestroyWindow(win);
    SDL_GL_DestroyContext(context);
    win = NULL;

    SDL_Quit();

    return 0;
}
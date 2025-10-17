#include <framework.h>

bool initGLAD()
{
    bool result = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    if(!result) {
        std::cout << "Failed to initialize GLAD!" << std::endl;
    }

    return result;
}

bool initFramework()
{
    return true;
}
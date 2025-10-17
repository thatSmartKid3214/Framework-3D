#ifndef FRAMEWORK_H
#define FRAMEWORK_H


#include "gl_stuff/buffers.h"
#include "gl_stuff/shader.h"
#include "platform/window.h"

#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <SDL3/SDL.h>

bool initGLAD();
bool initFramework();


#endif
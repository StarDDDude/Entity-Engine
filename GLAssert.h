#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>



#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(std::string function, const char* file, int line);
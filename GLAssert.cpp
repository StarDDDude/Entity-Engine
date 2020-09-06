#include <GL/glew.h>
#include "GLAssert.h"




void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(std::string function, const char* file, int line)
{
    while (GLenum error = glGetError()){
        std::cout << "------------------------------------------------------------------------------------------------\n";
        std::cout << "[OpenGL Error]: " << std::showbase << std::hex << error << std::dec << std::noshowbase << " | ";
        switch(error){
            case 0x0500 : std::cout << "GL_INVALID_ENUM\n"; break;
            case 0x0501 : std::cout << "GL_INVALID_VALUE\n"; break;
            case 0x0502 : std::cout << "GL_INVALID_OPERATION\n"; break;
            case 0x0503 : std::cout << "GL_STACK_OVERFLOW\n"; break;
            case 0x0504 : std::cout << "GL_STACK_UNDERFLOW\n"; break;
            case 0x0505 : std::cout << "GL_OUT_OF_MEMORY\n"; break;
            case 0x0506 : std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION\n"; break;
            case 0x0507 : std::cout << "GL_CONTEXT_LOST\n"; break;
            case 0x8031 : std::cout << "GL_TABLE_TOO_LARGE\n"; break;
        }
        std::cout << "[Function]:     " << function << ";\n";
        std::cout << "[File]:         " << file << " | [Line]:" << line << "\n";
        function.erase(function.begin() + function.find('('), function.end());
        std::cout << "[Page]:         " << "https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/" << function << ".xhtml\n";
        std::cout << "------------------------------------------------------------------------------------------------\n";
        return false;
    }
    return true;
}
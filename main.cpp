#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "GLAssert.h"
#include "block.h"


int main(void){
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(540, 540, "Boxes", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    if(glewInit() != GLEW_OK){
        std::cout << "glewInit error" << std::endl;
    }

    block* boi1 = new block(-30, 0, 0, 10);
    block* boi2 = new block(80, 0, 180, 5);

    while(!glfwWindowShouldClose(window))
    {   
        glClear(GL_COLOR_BUFFER_BIT);
        boi1->update();
        boi2->update();

        if ((boi1->Xpos + boi1->size) > (boi2->Xpos - boi2->size)){
            boi1->back();
            boi2->back();
            boi1->direction = 180;
            boi2->direction = 0;
        }

        boi1->draw();
        boi2->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
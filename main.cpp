#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "block.h"

int main(void){
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(950, 540, "Boxes", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    if(glewInit() != GLEW_OK){
        std::cout << "glewInit error" << std::endl;
    }

    block* boi1 = new block(10, 100, 0, 10);
    block* boi2 = new block(100, 100, 180, 5);

    while(!glfwWindowShouldClose(window))
    {
        boi1->update();
        boi2->update();

        if ((boi1->Xpos + boi1->size) > (boi2->Xpos - boi2->size)){
            boi1->back();
            boi2->back();
            boi1->direction = 180;
            boi2->direction = 0;
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
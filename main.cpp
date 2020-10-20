#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <time.h>
#include <vector>

#include "GLAssert.h"
#include "block.h"
#include "system.h"
#include "shader.h"


int main(void){
    GLFWwindow* window;
    srand(time(NULL));

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


   shader wooow("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");

    /*! @brief Vector holding pointers to Objects that can be of multiple different types.
     * 
     * At the start of each Entity is listed its type.
     * 
     * @param[in] GettingType *(unsigned char*)Entities[i]
     * @param[in] GettingMember *(<Type>*)Entities[i].<member>
     */
    std::vector<void*> Entities;

    Entities.reserve(8);
    Entities.emplace_back( new block(wooow.program) );
    Entities.emplace_back( new block(wooow.program) );

    int view = 1;
    while(!glfwWindowShouldClose(window))
    {
        view += 1;
        GLCall(glUniform1f(glGetUniformLocation(wooow.program, "view"), float(view)));


        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Update(&Entities);

        CheckCollisions(&Entities, wooow.program);


        
        for (int i=0; i<Entities.size(); i++){
            switch(*(unsigned char*)Entities[i]){
                case 0 : (*(block*)Entities[i]).draw(); break;
                default: std::cout << "Please fix your bullshit"; std::cout.flush();
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
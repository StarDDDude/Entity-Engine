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
#include "renderer.h"


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


    /*! @brief Vector holding pointers to Objects that can be of multiple different types.
     * 
     * At the start of each Entity is listed its type as an unsigned char.
     * 
     * @param[in] GettingType *(unsigned char*)Entities[i]
     * @param[in] GettingMember *(<Type>*)Entities[i].<member>
     */
    std::vector<void*> Entities;

    renderer render;
    shader shade("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");

    Entities.reserve(30);
    Entities.emplace_back( new block );
    render.CreateSquareData();                          //Manually Creating data to draw object
    Entities.emplace_back( new block() );
    Entities.emplace_back( new block() );
    Entities.emplace_back( new block() );
    Entities.emplace_back( new block() );
    Entities.emplace_back( new block() );

    float view = 100;
    bool direct = true;
    while(!glfwWindowShouldClose(window))
    {
        view += 1 * (direct*2-1);
        if(view >= 200){     //Upper Limit
            direct = false;
        } else
        if(view <= 50){    //Lower Limit
            direct = true;
        }
        GLCall(glUniform1f(glGetUniformLocation(shade.program, "view"), float(view)));


        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Update(&Entities, view);
        CheckCollisions(&Entities, shade.program);  //After Update cause it moves the entities back

        render.draw(&Entities, shade.program);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
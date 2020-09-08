#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "GLAssert.h"
#include "block.h"

bool DoTouch(block *boi1, block *boi2){
    if (((boi1->Xpos + boi1->size) > (boi2->Xpos - boi2->size)) &&
        ((boi1->Xpos - boi1->size) < (boi2->Xpos + boi2->size)) &&
        ((boi1->Ypos + boi1->size) > (boi2->Ypos - boi2->size)) &&
        ((boi1->Ypos - boi1->size) < (boi2->Ypos + boi2->size))){
            boi1->back();
            boi2->back();

            boi1->direction = 180;
            boi2->direction = 0;

            return true;
        }
    return false;
}

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



    //
    //
    //

    const char* VS_src = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "uniform vec2 Pos;"
        "\n"
        "void main(){\n"
        "\n"
        "gl_Position = position + vec4(Pos, 0.0f,0.0f);\n"
        "\n"
        "}";
    
    const char* FS_src = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main(){\n"
        "\n"
        "color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        "\n"
        "}";


    GLuint VS_ID, FS_ID, program;


    program = glCreateProgram();

    VS_ID = glCreateShader(GL_VERTEX_SHADER);
    FS_ID = glCreateShader(GL_FRAGMENT_SHADER);

    GLCall(glShaderSource(VS_ID, 1, &VS_src, nullptr));
    GLCall(glCompileShader(VS_ID));
    int result;
    GLCall(glGetShaderiv(VS_ID, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE){
        int lenght;
        GLCall(glGetShaderiv(VS_ID, GL_INFO_LOG_LENGTH, &lenght));
        char* message = (char*)alloca(lenght * sizeof(char));
        GLCall(glGetShaderInfoLog(VS_ID, lenght, &lenght, message));

        std::cout << "shader failed to compile" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(VS_ID);
    }


    GLCall(glShaderSource(FS_ID, 1, &FS_src, nullptr));
    GLCall(glCompileShader(FS_ID));
    GLCall(glGetShaderiv(FS_ID, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE){
        int lenght;
        glGetShaderiv(FS_ID, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(FS_ID, lenght, &lenght, message);

        std::cout << "shader failed to compile" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(VS_ID);
    }

    GLCall(glAttachShader(program, VS_ID));
    GLCall(glAttachShader(program, FS_ID));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(VS_ID));
    GLCall(glDeleteShader(FS_ID));

    GLCall(glUseProgram(program));


    std::vector<block> Entities;

    Entities.push_back({ block(0, 0, 0, 3, program) });
    Entities.push_back({ block(80, 0, 180, 1, program) });

    while(!glfwWindowShouldClose(window))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        for (int i=0; i<Entities.size(); i++){
            Entities[i].update(); 
        }

        if (DoTouch(&Entities[0], &Entities[1])){
            Entities.push_back({ block(30, 40, 0, 1, program) });
        }

        /*if ((Entities[0].Xpos + Entities[0].size) > (Entities[1].Xpos - Entities[1].size)){
            Entities[0].back();
            Entities[1].back();

            Entities[0].direction = 180;
            Entities[1].direction = 0;

            Entities.push_back({ block(30, 40, 0, 1, program) });
        }*/

        if ((Entities[0].Xpos - Entities[0].size) < -100){
            Entities[0].back();
            Entities[0].direction = 0;
        }
        if ((Entities[1].Xpos + Entities[1].size) > 100){
            Entities[1].back();
            Entities[1].direction = 180;
        }


        for (int i=0; i<Entities.size(); i++){
            Entities[0].draw(Entities[i]); 
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
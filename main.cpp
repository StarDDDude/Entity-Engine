#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <time.h>
#include <vector>

#include "GLAssert.h"
#include "block.h"


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
        "uniform vec4 Col;"
        "\n"
        "void main(){\n"
        "\n"
        "color = Col;\n"
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


    std::vector<void*> Entities;
    //Entity array that can index to multiple different types
    //Type of Entity is Defined at the beginning of the object in an unsigned char
    
    //General definition of getting type:
    //*(unsigned char*)Entities[n]
    
    //General definition of getting object member with known type:
    //(*(<Type>*)Entities[n]).<member>


    while(!glfwWindowShouldClose(window))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        for (int i=0; i < Entities.size(); i++){
            switch(*(unsigned char*)Entities[i]){
                case 0 : (*(block*)Entities[i]).update(); (*(block*)Entities[i]).wall(); break;
                default: std::cout << "Please fix your bullshit"; std::cout.flush(); 
            }
        }

        for (int i1=0, i2=1; i2 < Entities.size();){
            unsigned int Type1 = *(unsigned char*)Entities[i1];
            unsigned int Type2 = *(unsigned char*)Entities[i2];

            if ((Type1 == 0) && (Type2 == 0)){
                (*(block*)Entities[i1]).BlockTouch((block*)Entities[i2], &Entities, program);
            }

            i2++;
            if(i2 >= Entities.size()){
                i1++;
                i2 = i1+1;
            }
        }

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
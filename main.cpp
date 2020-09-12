#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "GLAssert.h"
#include "block.h"

void DoTouch(block *boi1, block *boi2, std::vector<block> *EntityArray, int program){

    int Xdistance = abs(boi1->Xpos - boi2->Xpos) - (boi1->size + boi2->size);
    int Ydistance = abs(boi1->Ypos - boi2->Ypos) - (boi1->size + boi2->size);

    if ((Xdistance < 0) && (Ydistance < 0)){
        boi1->touch(Xdistance, Ydistance);
        boi2->touch(Xdistance, Ydistance);
        EntityArray->push_back({ block(0, 40, 10, 3, 2, program) });
    }
}

void draw(block *boi){
    GLCall(glBindVertexArray(boi->VertexA_ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, boi->VertexB_ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boi->Index_ID));

    GLCall(glUseProgram(boi->program));
    GLCall(glUniform2f(glGetUniformLocation(boi->program, "Pos"), float(boi->Xpos)/100.0f, float(boi->Ypos)/100.0f));

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
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

    Entities.push_back({ block(0, 0, 350, 1, 3, program) });
    Entities.push_back({ block(85, 0, 190, 1, 1, program) });

    while(!glfwWindowShouldClose(window))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        for (int i=0; i < Entities.size(); i++){
            Entities[i].update();
            Entities[i].wall(); 
        }

        for (int i1=0, i2=1; i2 < Entities.size();){
            
            DoTouch(&Entities[i1], &Entities[i2], &Entities, program);

            i2++;
            if(i2 >= Entities.size()){
                i1++;
                i2 = i1+1;
            }
        }

        for (int i=0; i<Entities.size(); i++){
            draw(&Entities[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
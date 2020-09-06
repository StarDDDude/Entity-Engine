#include "block.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <math.h>

#include "GLAssert.h"

block::block(int i_Xpos, int i_Ypos, int i_direction, int i_speed){
    direction = i_direction;
    speed = i_speed;
    Xpos = i_Xpos;
    Ypos = i_Ypos;
    size = 5;

    float g_verticies[8]{                        //g_ for graphics related variables and functions
        float(Xpos-size)/100.0f, float(Ypos-size)/100.0f,
        float(Xpos+size)/100.0f, float(Ypos-size)/100.0f,
        float(Xpos+size)/100.0f, float(Ypos+size)/100.0f,
        float(Xpos-size)/100.0f, float(Ypos+size)/100.0f,
    };
   
    unsigned int g_indicies[6]{
        0,1,2,
        0,2,3,
    };

    
    GLCall(glGenBuffers(1, &VertexB_ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexB_ID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), g_verticies, GL_STATIC_DRAW));
    
    GLCall(glGenVertexArrays(1, &VertexA_ID));
    GLCall(glBindVertexArray(VertexA_ID));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0));

    GLCall(glGenBuffers(1, &Index_ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_ID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), g_indicies, GL_STATIC_DRAW));

    //
    //
    //

    const char* VS_src = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main(){\n"
        "\n"
        "gl_Position = position;\n"
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

}

void block::update(){
    Xpos = Xpos + speed * cos(direction*M_PI/180);
    Ypos = Ypos + speed * sin(direction*M_PI/180);
}

void block::back(){
    Xpos = Xpos - speed * cos(direction*M_PI/180);
    Ypos = Ypos - speed * sin(direction*M_PI/180);
}

void block::draw(){
    GLCall(glBindVertexArray(VertexA_ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexB_ID));

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
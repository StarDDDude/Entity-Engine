#include "block.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <math.h>

#include "GLAssert.h"

block::block(int i_Xpos, int i_Ypos, int i_direction, int i_speed, unsigned int i_program){
    direction = i_direction;
    speed = i_speed;
    Xpos = i_Xpos;
    Ypos = i_Ypos;
    size = 5;
    program = i_program;

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
}

void block::update(){
    Xpos = Xpos + speed * cos(direction*M_PI/180);
    Ypos = Ypos + speed * sin(direction*M_PI/180);
}

void block::back(){
    Xpos = Xpos - speed * cos(direction*M_PI/180);
    Ypos = Ypos - speed * sin(direction*M_PI/180);
}

void block::draw(block Uniform){
    GLCall(glBindVertexArray(VertexA_ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexB_ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_ID));

    GLCall(glUseProgram(program));
    GLCall(glUniform2f(glGetUniformLocation(program, "Pos"), float(Uniform.Xpos)/100.0f, float(Uniform.Ypos)/100.0f));

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

}
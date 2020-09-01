#include "block.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <math.h>

block::block(int i_Xpos, int i_Ypos, int i_direction, int i_speed){
    direction = i_direction;
    speed = i_speed;
    Xpos = i_Xpos;
    Ypos = i_Ypos;
    size = 5;

    float g_verticies[8]{                        //g_ for graphics related variable and functions
        Xpos - size, Ypos - size,
        Xpos + size, Ypos - size,
        Xpos + size, Ypos + size,
        Xpos - size, Ypos + size,
    };
   
    unsigned int g_indicies[6]{
        0,1,2,
        0,2,3,
    };
    
    glGenBuffers(1, &VertexB_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexB_ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_verticies)*sizeof(float), g_verticies, GL_STATIC_DRAW);

    glGenBuffers(1, &Index_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indicies)*sizeof(unsigned int), g_indicies, GL_STATIC_DRAW);
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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexB_ID);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
#include "block.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <math.h>
#include <random>
#include <time.h>


#include "GLAssert.h"

block::block(int i_Xpos, int i_Ypos, int i_direction, int i_speed, unsigned int i_size, unsigned int i_program){
    direction = i_direction;
    speed = i_speed;
    Xpos = i_Xpos;
    Ypos = i_Ypos;
    size = i_size;
    program = i_program;
    srand(time(NULL));

    float g_verticies[8]{                        //g_ for graphics related variables and functions
        float(-size)/100.0f, float(-size)/100.0f,
        float(+size)/100.0f, float(-size)/100.0f,
        float(+size)/100.0f, float(+size)/100.0f,
        float(-size)/100.0f, float(+size)/100.0f,
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

void block::touch(int Xdistance, int Ydistance){
    back();
    if (Xdistance > Ydistance){
        direction += 180 - direction - (direction*int((direction > 90) && (direction < 270))) + (rand() % 20 -10);
    } else {
        direction += 180 - (direction - 90) - (direction + 90) + (rand() % 20 -10);
    }
}

void block::wall(){
    if((Xpos - size) < -100){
        back();
        direction += 180 - direction-direction + (rand() % 20 -10);
    } else if((Xpos + size) > 100){
        back();
        direction += 180 - direction-direction + (rand() % 20 -10);
    } else if((Ypos - size) < -100){
        back();
        direction += 180 - (direction + 90)-(direction + 90) + (rand() % 20 -10);
    } else if((Ypos + size) > 100){
        back();
        direction += 180 - (direction + 90)-(direction + 90) + (rand() % 20 -10);
    }
}
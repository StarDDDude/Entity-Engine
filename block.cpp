#include "block.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <math.h>
#include <random>


#include "GLAssert.h"

block::block(unsigned int i_program){
    size = rand() % 3+1;
    direction = rand() % 360+1;
    speed = rand() % 4+1;
    Xpos = rand() % int(201 - 2*size) - (100 - size);
    Ypos = rand() % int(201 - 2*size) - (100 - size);
    R = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    G = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    B = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    program = i_program;

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

void block::draw(){
    GLCall(glBindVertexArray(VertexA_ID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexB_ID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index_ID));

    GLCall(glUseProgram(program));
    GLCall(glUniform2f(glGetUniformLocation(program, "Pos"), float(Xpos)/100.0f, float(Ypos)/100.0f));
    GLCall(glUniform4f(glGetUniformLocation(program, "Col"), R, G, B, 1.0));

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void block::update(){
    Xpos = Xpos + speed * cos(direction*M_PI/180);
    Ypos = Ypos + speed * sin(direction*M_PI/180);
}

void block::back(){
    Xpos = Xpos - speed * cos(direction*M_PI/180);
    Ypos = Ypos - speed * sin(direction*M_PI/180);
}

void block::OnTouch(int Xdistance, int Ydistance){
    back();
    if (Xdistance > Ydistance){
        direction += 180 - direction - (direction*int((direction > 90) && (direction < 270))) + (rand() % 20 -10);
    } else {
        direction += 180 - (direction - 90) - (direction + 90) + (rand() % 20 -10);
    }
}

void block::BlockTouch(block *Obj, std::vector<block> *EA, int program){
    int Xdistance = abs(Xpos - Obj->Xpos) - (size + Obj->size);
    int Ydistance = abs(Ypos - Obj->Ypos) - (size + Obj->size);

    if ((Xdistance < 0) && (Ydistance < 0)){
        OnTouch(Xdistance, Ydistance);
        Obj->OnTouch(Xdistance, Ydistance);
        EA->push_back({ block(program) });
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
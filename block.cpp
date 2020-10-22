#include "block.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GLAssert.h"

#include <math.h>
#include <random>



block::block()
    : type(0)
{
    size = 1+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3));
    direction = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/360));
    speed = 1+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4));
    Xpos = rand() % int(201 - 2*size) - (100 - size);
    Ypos = rand() % int(201 - 2*size) - (100 - size);
    
    
    R = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    G = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    B = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

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

void block::BlockTouch(block *Obj, std::vector<void*> *EA, unsigned int program){
    int Xdistance = abs(Xpos - Obj->Xpos) - (size + Obj->size);
    int Ydistance = abs(Ypos - Obj->Ypos) - (size + Obj->size);

    if ((Xdistance < 0) && (Ydistance < 0)){
        OnTouch(Xdistance, Ydistance);
        Obj->OnTouch(Xdistance, Ydistance);
        EA->push_back({ new block() });
    }
}


void block::wall(int wall){

    if((Xpos - size) < (wall * -1)){
        back();
        direction += 180 - direction-direction + (rand() % 20 -10);
    } else if((Xpos + size) > wall){
        back();
        direction += 180 - direction-direction + (rand() % 20 -10);
    } else if((Ypos - size) < (wall * -1)){
        back();
        direction += 180 - (direction + 90)-(direction + 90) + (rand() % 20 -10);
    } else if((Ypos + size) > wall){
        back();
        direction += 180 - (direction + 90)-(direction + 90) + (rand() % 20 -10);
    }
}

void block::output(){
    std::cout << "a";
}
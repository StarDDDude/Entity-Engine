#include "block.h"

#include <math.h>

block::block(int i_Xpos, int i_Ypos, int i_direction, int i_speed){
    direction = i_direction;
    speed = i_speed;
    Xpos = i_Xpos;
    Ypos = i_Ypos;
    size = 5;

}

void block::update(){
    Xpos = Xpos + speed * cos(direction*M_PI/180);
    Ypos = Ypos + speed * sin(direction*M_PI/180);
}

void block::back(){
    Xpos = Xpos - speed * cos(direction*M_PI/180);
    Ypos = Ypos - speed * sin(direction*M_PI/180);
}
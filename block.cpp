#include "block.h"

#include <math.h>

block::block(int i_direction, int i_speed){
    direction = i_direction;
    speed = i_speed;
    Xpos = 0;
    Ypos = 0;

}

void block::update(){
    Xpos = Xpos + speed * cos(direction*M_PI/180);
    Ypos = Ypos + speed * sin(direction*M_PI/180);
}
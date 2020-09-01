#pragma once

class block {
public:
    int Xpos;
    int Ypos;
    int size;    
    int direction;
    int speed;

    block(int i_Xpos, int i_Ypos, int i_direction, int i_speed);        //i_ for inititializer variables
    void update();
    void back();
};
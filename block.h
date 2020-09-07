#pragma once

class block {
public:
    int Xpos;
    int Ypos;
    int size;    
    int direction;
    int speed;

    unsigned int VertexB_ID;
    unsigned int VertexA_ID;
    unsigned int Index_ID;
    unsigned int program;

    block(int i_Xpos, int i_Ypos, int i_direction, int i_speed, unsigned int i_program);        //i_ for inititializer variables
    void update();
    void back();
    void draw(block uniform);
};
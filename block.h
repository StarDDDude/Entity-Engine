#pragma once

class block {
public:
    float Xpos;
    float Ypos;
    float size;    
    float direction;
    float speed;

    unsigned int VertexB_ID;
    unsigned int VertexA_ID;
    unsigned int Index_ID;
    unsigned int program;

    block(int i_Xpos, int i_Ypos, int i_direction, int i_speed, unsigned int i_size, unsigned int i_program);        //i_ for inititializer variables
    void update();
    void back();
    void touch(int Xdistance, int Ydistance);
    void wall();
    void draw(block uniform);
};
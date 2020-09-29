#pragma once


#include <vector>

class block {
public:
    unsigned char Type;
    float Xpos;
    float Ypos;
    float size;    
    float direction;
    float speed;

    float R;
    float G;
    float B;

    unsigned int VertexB_ID;
    unsigned int VertexA_ID;
    unsigned int Index_ID;
    unsigned int program;

    block(unsigned int i_program);        //i_ for inititializer variables
    void update();
    void back();
    void OnTouch(int Xdistance, int Ydistance);
    void BlockTouch(block *boi2, std::vector<void*> *EA, int program);
    void wall();
    void draw();

    void output();
};
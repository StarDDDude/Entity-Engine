#pragma once


#include <vector>

class block {
public:
    unsigned char type;
    float Xpos;
    float Ypos;
    float size;    
    float direction;
    float speed;

    float R;
    float G;
    float B;

    static unsigned int VertexB_ID;
    static unsigned int VertexA_ID;
    static unsigned int Index_ID;
    static unsigned int FIRST_VertexB_ID;
    static unsigned int FIRST_VertexA_ID;
    static unsigned int FIRST_Index_ID;
    unsigned int program;

    block(unsigned int i_program);        //i_ for inititializer variables
    void update();
    void back();
    void OnTouch(int Xdistance, int Ydistance);
    void BlockTouch(block *boi2, std::vector<void*> *EA, unsigned int program);
    void wall(int wall);
    void draw();

    void output();
};
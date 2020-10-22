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

    block();
    void update();
    void back();
    void OnTouch(int Xdistance, int Ydistance);
    void BlockTouch(block *boi2, std::vector<void*> *EA, unsigned int program);
    void wall(int wall);
    void draw();

    void output();
};
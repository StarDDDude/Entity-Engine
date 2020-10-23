#pragma once


#include <vector>

class block
{
public:     //Data
    unsigned char type;
    float Xpos;
    float Ypos;
    float size;
    float direction;
    float speed;

    float R;
    float G;
    float B;


public:     //Functions
    block();
    ~block();

    void update();
    void back();
    void OnTouch(int Xdistance, int Ydistance);
    void BlockTouch(block *boi2, std::vector<void*> *EA);
    void wall(int wall);
    void draw();
};
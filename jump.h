#pragma once

#include "block.h"

#include <vector>


class jump
{
public:     //Data
    unsigned char type;
    float Xpos;
    float Ypos;
    float size;
    //float direction;
    //float speed;

    float accel;

    float R;
    float G;
    float B;


public:     //Functions
    jump();
    ~jump();

    void update();
    void back();
    void OnTouch(int Yside);
    void BlockTouch(block *boi2);
    void wall(int wall);
    void draw();
};
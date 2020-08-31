#pragma once

class block {
private:
    int Xpos;
    int Ypos;
    int size;
public:
    block(int i_direction, int i_speed);        //i_ for inititializer variables
    void update();
    
    int direction;
    int speed;
};
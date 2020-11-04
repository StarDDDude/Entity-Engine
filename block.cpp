#include "block.h"
#include <GL/glew.h>

#include "GLAssert.h"

#include <random>



block::block()
    : type(0)
{
    size = 1+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3));
    direction = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/360));
    speed = 0;//1+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4));
    Xpos = 0;//rand() % int(201 - 2*size) - (100 - size);
    Ypos = -50;//rand() % int(201 - 2*size) - (100 - size);
    
    
    R = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    G = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    B = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    

    //Syntax for generating random numbers:
    //Float:    <Low Limit>+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/<High Limit>))
    //Integer:  rand() % int(<Area>) - (<Offset>);
}

block::~block()
{
    
}

/*! @brief moves object forwards into direction */
void block::update()
{
    Xpos = Xpos + speed * cos(direction*M_PI/180);
    Ypos = Ypos + speed * sin(direction*M_PI/180);
}

/*! @brief moves object backwards into direction */
void block::back()
{
    Xpos = Xpos - speed * cos(direction*M_PI/180);
    Ypos = Ypos - speed * sin(direction*M_PI/180);
}

/*! @brief changes direction of block
 *
 * Needs X|Ydistance to touched object to evaluate which side it touched 
 *  
 * @param[in] Xdistance Distance to other object on X axis
 * @param[in] Ydistance Distance to other object on Y axis
*/
void block::OnTouch(int Xdistance, int Ydistance)
{
    back();
    if (Xdistance > Ydistance){ //X-Side:
        direction += 180 - direction - (direction*int((direction > 90) && (direction < 270))) + (rand() % 20 -10);
    } else {    //Y-Side:
        direction += 180 - (direction - 90) - (direction + 90) + (rand() % 20 -10);
    }
}

/*! @brief collision routine, called when touching another block
 * 
 * Handles collision for booth itself and the other block
 *  
 * @param[in] Obj Pointer to other touched object
 * @param[in] Entities Entity Array that holds the objects, used to create new block
*/
void block::BlockTouch(block *Obj, std::vector<void*> *Entities)
{
    //[1]:
    int Xdistance = abs(Xpos - Obj->Xpos) - (size + Obj->size);
    int Ydistance = abs(Ypos - Obj->Ypos) - (size + Obj->size);

    //[2]
    if ((Xdistance < 0) && (Ydistance < 0)){
        OnTouch(Xdistance, Ydistance);
        Obj->OnTouch(Xdistance, Ydistance);
        Entities->push_back({ new block() });
    }

    //1. [X|Ydistance]: saves distance in X and Y axis
    //2. [if]: boxes collide if booth their X and Y distance are lower than 0
}

/*! @brief Makes ball bounce off of bounds
 *
 * makes block bounce off when it goes out of the specified boundary box
 * Bndary box geseated as distance in X or Y direction awaya from (0/0)
 * 
 * @param[in] wall the boundary box
 */
void block::wall(int wall)
{

    if((Xpos - size) < (wall * -1)){        //Left
        back();
        direction += 180 - direction-direction + (rand() % 20 -10);
    } else if((Xpos + size) > wall){        //Right
        back();
        direction += 180 - direction-direction + (rand() % 20 -10);
    } else if((Ypos - size) < (wall * -1)){ //Down
        back();
        direction += 180 - (direction + 90)-(direction + 90) + (rand() % 20 -10);
    } else if((Ypos + size) > wall){        //Up
        back();
        direction += 180 - (direction + 90)-(direction + 90) + (rand() % 20 -10);
    }
}
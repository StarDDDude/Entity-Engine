#include "jump.h"
#include <GL/glew.h>

#include "GLAssert.h"

#include <random>



jump::jump()
    : type(1), accel(0)
{
    size = 7;// 1+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3));
    //speed = 1+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4));
    Xpos = 0;//rand() % int(201 - 2*size) - (100 - size);
    Ypos = -0 + size;//rand() % int(201 - 2*size) - (100 - size);
    
    
    R = 150;//static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    G = 150;//static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    B = 150;//static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


    //Syntax for generating random numbers:
    //Float:    <Low Limit>+static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/<High Limit>))
    //Integer:  rand() % int(<Area>) - (<Offset>);
}

jump::~jump()
{
    
}

/*! @brief moves object forwards into direction */
void jump::update()
{
    Ypos += accel;
    accel -= 0.1f;
}

/*! @brief moves object backwards into direction */
void jump::back()
{
    Ypos -= accel + 0.5f;
}

/*! @brief moves object
 *
 *  
 * @param[in] Yside Variable deciding wether object is tuched from above, if value positive object is above
 * 
 */
void jump::OnTouch(int Yside)
{
    back();
    if (Yside > 0){
        Ypos += accel + 0.1f;
        accel = 6.5;
    } else {
        Ypos -= accel + 0.1f;
        accel *= -0.6;
    }
}

/*! @brief collision routine, called when touching another block
 * 
 * Handles collision for booth itself and the other block
 *  
 * @param[in] Obj Pointer to other touched object
 * @param[in] Entities Entity Array that holds the objects, used to create new block
*/
void jump::BlockTouch(block *Obj)
{
    //[1]:
    int Xdistance = abs(Xpos - Obj->Xpos) - (size + Obj->size);
    int Ydistance = abs(Ypos - Obj->Ypos) - (size + Obj->size);

    int Yside = Xpos - Obj->Xpos;

    //[2]
    if ((Xdistance < 0) && (Ydistance < 0)){
        OnTouch(Yside);
        Obj->OnTouch(Xdistance, Ydistance);
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
void jump::wall(int wall)
{
    if((Xpos - size) < (wall * -1)){        //Left

    } else if((Xpos + size) > wall){        //Right

    } else if((Ypos - size) < (wall * -1)){ //Down
        Ypos += accel;
        accel = 6.5;
    } else if((Ypos + size) > wall){        //Up
        Ypos -= accel + 0.1f;
        accel *= -0.6;
    }
}
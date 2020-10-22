#include "math.h"
#include <vector>
#include <iostream>

#include "system.h"

/*! @brief Collision between two circles */
bool CollideCC(float XPos1, float YPos1, float Radius1, float XPos2, float YPos2, float Radius2)
{
    float SideX = abs(XPos1-XPos2);
    float SideY = abs(YPos1-YPos2);
    SideX = SideX*SideX;
    SideY = SideY*SideY;
    float distance = sqrt(SideY + SideX);

    return (distance < (Radius1 + Radius2));
}

/*! @brief Collision between two rectangles */
bool CollideRR(float XPos1, float YPos1, float SizeX1, float SizeY1, float XPos2, float YPos2, float SizeX2, float SizeY2)
{
    float EdgeL1 = XPos1 - SizeX1;
    float EdgeR1 = XPos1 + SizeX1;
    float EdgeB1 = XPos1 - SizeY1;
    float EdgeT1 = XPos1 + SizeY1;

    float EdgeL2 = XPos2 - SizeX2;
    float EdgeR2 = XPos2 + SizeX2;
    float EdgeB2 = XPos2 - SizeY2;
    float EdgeT2 = XPos2 + SizeY2;


    return (EdgeL1 < EdgeR2 && EdgeR1 > EdgeL2) && (EdgeB1 < EdgeT2 && EdgeT1 > EdgeB2);
}

/*! @brief Collision between a retangle and a Circle */
bool CollideCR(float XPosR, float YPosR, float SizeXR, float SizeYR, float XPosC, float YPosC, float RadiusC)
{
    float DistanceX = abs(XPosR - XPosC);
    float DistanceY = abs(YPosR - YPosC);

    if (DistanceX > (SizeXR + RadiusC)) { return false; }
    if (DistanceY > (SizeYR + RadiusC)) { return false; }

    float cDist_sq = (DistanceX - SizeXR)*(DistanceX - SizeXR) + (DistanceY - SizeYR)*(DistanceY - SizeYR);
    if(cDist_sq > (RadiusC*RadiusC)) { return false; }

    return true;
}

//^Collision functions not yet implemented


void update(std::vector<void*> *Entities, int wall)
{

    for(int i=0; i<Entities->size(); i++){
        //[1]:
        unsigned char type = *(unsigned char*)(*Entities)[i];
        switch(type){
        case 0 :
            //[2]:
            (*(block*)(*Entities)[i]).update();
            (*(block*)(*Entities)[i]).wall(wall);
            break;
        
        default:
            std::cout << "[ERROR]:Entity was detected with an invalid Entity ID" << std::endl;
            std::cout << "|-----|:renderer.cpp" << std::endl;
            std::cout.flush();
        }
        //1. [switch]:          Check object type to determine which update routine to call
        //2. [update|wall]:     Calls the entities update methods
        //  - update moves the entity into a direction
        //  - wall makes sure the enity doesn't fly out of bounds
        //    (Collsions with other objects ae checked in CheckCollisions)
    }
}

void CheckCollisions(std::vector<void*> *Entities, unsigned int program)
{
    for(int i=1, j=0; i < Entities->size();){
        //[1]:
        unsigned char TypeA = *(unsigned char*)(*Entities)[i];
        unsigned char TypeB = *(unsigned char*)(*Entities)[j];
        
        //[2]:
        if ((TypeA == 0) && (TypeB == 0)) {
            (*(block*)(*Entities)[j]).BlockTouch((block*)(*Entities)[i], Entities);
        }
        
        //[3]:
        i++;
        if(i >= Entities->size()){
            j++;
            i = j+1;
        }
    }

    //1. [TypeA|B]: Storing types of current collision pair
    //2. [if]: Check object type to determine which collision routine to call
    //  - Can't use switch as it can only take in a single parameter
    //3. [iterator]: handles iterating through every combination of 2 entities
}
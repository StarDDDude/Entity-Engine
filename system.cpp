#include "math.h"
#include <vector>
#include <iostream>

#include "system.h"


bool CollideCC(float XPos1, float YPos1, float Radius1, float XPos2, float YPos2, float Radius2){
    float SideX = abs(XPos1-XPos2);
    float SideY = abs(YPos1-YPos2);
    SideX = SideX*SideX;
    SideY = SideY*SideY;
    float distance = sqrt(SideY + SideX);

    return (distance < (Radius1 + Radius2));
}

bool CollideRR(float XPos1, float YPos1, float SizeX1, float SizeY1, float XPos2, float YPos2, float SizeX2, float SizeY2){
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

bool CollideCR(float XPosR, float YPosR, float SizeXR, float SizeYR, float XPosC, float YPosC, float RadiusC){
    float DistanceX = abs(XPosR - XPosC);
    float DistanceY = abs(YPosR - YPosC);

    if (DistanceX > (SizeXR + RadiusC)) { return false; }
    if (DistanceY > (SizeYR + RadiusC)) { return false; }

    float cDist_sq = (DistanceX - SizeXR)*(DistanceX - SizeXR) + (DistanceY - SizeYR)*(DistanceY - SizeYR);
    if(cDist_sq > (RadiusC*RadiusC)) { return false; }

    return true;
}

void CheckCollisions(){
    
}

void Update(std::vector<void*> *Entities){
    for(int i=0; i<Entities->size(); i++){
        unsigned char type = *(unsigned char*)(&Entities[i]);
        switch(type){
            case 0 : (*(block*)&Entities[i]).update(); break;
            default: std::cout << "[ERROR]:Entity was detected with an invalid Entity ID" << std::endl; std::cout.flush();
        }
    }
};
#pragma once

#include "block.h"

bool CollideCC(float XPos1, float YPos1, float Radius1, float XPos2, float YPos2, float Radius2);

bool CollideRR(float XPos1, float YPos1, float SizeX1, float SizeY1, float XPos2, float YPos2, float SizeX2, float SizeY2);

bool CollideCR(float XPosR, float YPosR, float SizeXR, float SizeYR, float XPosC, float YPosC, float RadiusC);

void CheckCollisions(std::vector<void*> *Entities, unsigned int program);

void Update(std::vector<void*> *Entities, int wall);
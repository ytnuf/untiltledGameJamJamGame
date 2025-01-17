#ifndef powerup_h
#define powerup_h

#include "circle.h"
#include "include.h"
#include "missile.h"

#define powerUpChance /*(0 - 1]*/ .001

bool shouldDropPowerup();

void applyPowerup(Missile* misArr, unsigned int misCount, circle* target);

int getClosestItemToPosition(circle* arr, int arrSize, Vector2 position);

bool shouldApplyPowerup(Camera2D camera, Missile* misArr, unsigned int misCount);

#endif

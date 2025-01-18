#ifndef powerup_h
#define powerup_h

#include "circle.h"
#include "include.h"
#include "missile.h"
#include "enemy.h"

#define timeSlowCode 1
#define deadeyeCode 2

#define powerUpChance /*(0 - 1]*/ .05
#define powerUpSlowTimeValue 2.25 /*this goes into 1/n (n being the value)*/
#define powerUpTimeTimeFreeze 10

#define powerUpTimeFreezeZoom 1
#define powerUpDeadeyeZoom .8

#define powerUpDeadeyeGive 100
#define powerUpDeadeyeTime 5

//returns which one
short shouldDropPowerup();

void applyPowerup(Missile* misArr, unsigned int misCount, circle* target);

int getClosestItemToPosition(circle* arr, int arrSize, Vector2 position);

//returns index of target if so, else -1
int shouldApplyPowerup(Camera2D camera, enemy* enArr, unsigned int enCount);

#endif

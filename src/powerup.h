#ifndef powerup_h
#define powerup_h

#include "circle.h"
#include "include.h"
#include "missile.h"
#include "enemy.h"

#define timeSlowCode 1
#define powerUpChance /*(0 - 1]*/ .02
#define powerUpSlowTimeValue 1.25 /*this goes into 1/n (n being the value)*/
#define powerUpTimeTimeFreeze 4   /*if this is *too* high youll be in time slow forever*/
#define powerUpTimeFreezeZoom 1.02

//returns which one
bool shouldDropPowerup(void);

#endif

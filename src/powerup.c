#include "powerup.h"
#include "circle.h"

bool shouldDropPowerup(void) {
  return randSingle() <= powerUpChance;
}

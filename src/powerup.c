#include "powerup.h"
#include "circle.h"

bool shouldDropPowerup() {
  return randSingle() <= powerUpChance;
}

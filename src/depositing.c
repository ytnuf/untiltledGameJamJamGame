#include "depositing.h"
#include "circle.h"
#include "player.h"
#include <math.h>
#include "../libraries/raylib.h"
#include "../libraries/raymath.h"

const float intakeRadSqr = baseIntakeRadius * baseIntakeRadius;

Base initBase(circle planet) {
  Base out;
  out.score = 0;
  out.intakeRadius = baseIntakeRadius;
  out.body.radius = baseRadius;
  out.body.colour = baseColour;
  out.planet = planet;
  out.angle = randSingle() * 2 * M_PI;
  setBasePosition(&out);
  return out;
}

void setBasePosition(Base* base) {
  base->body.position = Vector2Add((Vector2){cosf(base->angle) * base->planet.radius, sinf(base->angle) * base->planet.radius}, base->planet.position);
}

void drawBase(Base* base, Vector2 screenDimensions) {
  drawCircle(&base->body, screenDimensions);
}

bool positionInRangeOfBase(Base* base, Vector2 point) {
  return Vector2DistanceSqr(base->body.position, point) < intakeRadSqr;
}

void manageBase(Base* base, Player* player, Sound* collectionNoise, float delta) {
  base->angle += baseRotationRate * delta;
  setBasePosition(base);
  if(!positionInRangeOfBase(base, player->body.position))
    return;
  float scoreToAdd = scorePerOrb * delta * baseIntakeRate;
  if(scoreToAdd > player->score)
    scoreToAdd = player->score;
  player->score -= scoreToAdd;
  base->score += scoreToAdd;
  if(scoreToAdd >= .01 && !IsSoundPlaying(*collectionNoise))
    PlaySound(*collectionNoise);
}

void drawBorder(Base* base, Vector2 screenDimensions) {
  DrawCircleLinesV((Vector2){base->body.position.y + screenDimensions.x / 2.0f, -base->body.position.x + screenDimensions.y / 2.0f}, base->intakeRadius, baseIntakeBorderColour);
}

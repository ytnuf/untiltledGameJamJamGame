#include "depositing.h"
#include "circle.h"
#include "player.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>

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

void addScoreToBase(Base* base, float score) {
  base->score += score;
}

bool positionInRangeOfBase(Base* base, Vector2 point) {
  return Vector2Distance(base->body.position, point) < baseIntakeRadius;
}

void manageBase(Base* base, Player* player, float delta) {
  base->angle += rotationRate * delta;
  setBasePosition(base);
  if(!positionInRangeOfBase(base, player->body.position))
    return;
  float scoreToAdd = scorePerOrb * delta * intakeRate;
  if(scoreToAdd > player->score)
    scoreToAdd = player->score;
  player->score -= scoreToAdd;
  base->score += scoreToAdd;
}

void drawBorder(Base* base, Vector2 screenDimensions) {
  drawCircle(&(circle){base->body.position, base->intakeRadius, intakeBorderColour}, screenDimensions);
  drawCircle(&(circle){base->body.position, base->intakeRadius - intakeBorderThickn, BLACK}, screenDimensions);
}

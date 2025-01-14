#include "depositing.h"
#include "circle.h"
#include "player.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

Base initBase(circle planet) {
  Base out;
  out.score = 0;
  out.intakeRadius = baseIntakeRadius;
  out.body.radius = baseRadius;
  out.body.colour = baseColour;
  float angle = randSingle() * 2 * M_PI;
  out.body.position = Vector2Add((Vector2){cosf(angle) * planet.radius, sinf(angle) * planet.radius}, planet.position);
  printf("%f\n", 180 * angle / M_PI);
  return out;
}

void drawBase(Base* base) {
  drawCircle(&base->body);
}

void addScoreToBase(Base* base, float score) {
  base->score += score;
}

bool positionInRangeOfBase(Base* base, Vector2 point) {
  return Vector2Distance(base->body.position, point) < baseIntakeRadius;
}

void manageBase(Base* base, Player* player, float delta) {
  if(!positionInRangeOfBase(base, player->body.position))
    return;
  float scoreToAdd = scorePerOrb * delta;
  if(scoreToAdd > player->score)
    scoreToAdd = player->score;
  player->score -= scoreToAdd;
  base->score += scoreToAdd;
  printf("%f\n", base->score);
}

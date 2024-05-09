#pragma once
#include "body.h"
#include "raylib.h"

typedef struct lllBody;

extern lllBody* lllBodies;
extern int lllBodyCount;
extern Vector2 lllGravity;

lllBody* CreateBody(Vector2 position, float mass, lllBodyType bodyType);
void AddBody(lllBody* body);
void DestroyBody(lllBody* body);
void DestroyAllBody(lllBody* body);
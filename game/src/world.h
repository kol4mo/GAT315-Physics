#pragma once
#include "body.h"
#include "raylib.h"

typedef struct lllBody_t;

extern lllBody_t* lllBodies;
extern int lllBodyCount;
extern Vector2 lllGravity;

lllBody_t* CreateBody(Vector2 position, float mass, lllBodyType bodyType);
void AddBody(lllBody_t* body);
void DestroyBody(lllBody_t* body);
void DestroyAllBody(lllBody_t* body);
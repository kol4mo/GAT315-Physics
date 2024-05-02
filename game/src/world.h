#pragma once
#include "body.h"
#include "raylib.h"

typedef struct lllBody;

extern lllBody* lllBodies;
extern int lllBodyCount;
extern Vector2 lllGravity;

lllBody* CreateBody();
void DestroyBody(lllBody* body);
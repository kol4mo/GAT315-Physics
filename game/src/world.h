#pragma once
#include "body.h"

extern lllBody* lllBodies;
extern int lllBodyCount;

lllBody* CreateBody();
void DestroyBody(lllBody* body);
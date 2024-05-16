#pragma once
#include "raylib.h"
typedef struct ncContact ncContact_t;
typedef struct lllBody lllBody_t;

void CreateContacts(lllBody_t* bodies, ncContact_t** contacts);
ncContact_t* GenerateContact(lllBody_t* body1, lllBody_t* body2);

void SeparateContacts(ncContact_t* contacts);
void ResolveContacts(ncContact_t* contacts);

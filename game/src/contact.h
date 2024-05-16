#pragma once
#include "raylib.h"
#include "body.h"

typedef struct ncContact
{
	lllBody_t* body1;
	lllBody_t* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct ncContact* next;
} ncContact_t;

void AddContact(ncContact_t* contact, ncContact_t** contacts);
void DestroyAllContacts(ncContact_t** contacts);

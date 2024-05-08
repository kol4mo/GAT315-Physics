#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum {
	BT_STATIC,
	BT_KINEMATIC,
	BT_DYNAMIC
}lllBodyType;

typedef enum {
	FM_FORCE,
	FM_IMPULSE,
	FM_VELOCITY
}lllForceMode;

typedef struct lllBody {
	lllBodyType bodyType;
	//acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;
	Color* color;
	float mass;
	float inverseMass; // 1/mass (static = 0)
	float gravityScale;
	float damping;

	struct lllBody* next;
	struct lllBody* prev;

}lllBody;

inline void ApplyForce(lllBody* body, Vector2 force, lllForceMode forceMode) {
	if (body->bodyType != BT_DYNAMIC) {
		return;
	}

	switch (forceMode)
	{
	case FM_FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case FM_IMPULSE:
		//applys a sudden change in momentum
		body->velocity = Vector2Scale(force, body->inverseMass);
		break;
	case FM_VELOCITY:
		body->velocity = force;
		break;
	}
}

inline void ClearForce(lllBody* body) {
	body->force = Vector2Zero();
}

void Step(lllBody* body, float timestep);
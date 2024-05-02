#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum {
	STATIC,
	KINEMATIC,
	DYNAMIC
}lllBodyType;

typedef struct lllBody {
	lllBodyType bodyType;
	//force -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 force;

	float mass;
	float inverseMass; // 1/mass (static = 0)

	struct lllBody* next;
	struct lllBody* prev;

}lllBody;

inline void ApplyForce(lllBody* body, Vector2 force) {
	body->force = Vector2Add(body->force, force);
}

inline void ClearForce(lllBody* body) {
	body->force = Vector2Zero();
}
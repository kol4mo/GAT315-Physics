#pragma once
#include "body.h"

inline void ExplicitEuler(lllBody_t* body, float timestep) {
	//Vector2 acceleration = body->force * body->inverseMass;
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timestep));
}
inline void SemiImplicitEuler(lllBody_t* body, float timestep) {
	//Vector2 acceleration = body->force * body->inverseMass;
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timestep));
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
}
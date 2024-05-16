#pragma once
#include "body.h"
#include "integrator.h"
#include "world.h"

void Step(lllBody_t* body, float timestep) {
	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(lllGravity, body->gravityScale), body->mass));
	body->acceleration = Vector2Scale(body->force, body->inverseMass);

	SemiImplicitEuler(body, timestep);

	//apply damping
	float damping = 1 / (1 + timestep * body->damping);
	body->velocity = Vector2Scale(body->velocity, damping);
	ClearForce(body);
}
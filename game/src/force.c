#pragma once
#include "force.h"
#include "body.h"
#include "mathf.h"
void ApplyGravitation(lllBody* bodies, float strength) {
	for (lllBody* body1 = bodies; body1; body1 = body1->next)
	{
		for (lllBody* body2 = bodies; body2; body2 = body2->next)
		{
			if (body1 == body2) {
				continue;
			}

			Vector2 direction = Vector2Subtract(body1->position, body2->position);//body1->position - body2->position;
			float distance = Vector2Length(direction);//<get length of vector>

			distance = fmaxf(1, distance);
			float force = (body1->mass * body2->mass / (distance * distance)) * strength;

			direction = Vector2Normalize(direction);//<scale normalized direction vector by force>;

			ApplyForce(body1, Vector2Scale(direction, -force), FM_FORCE);
			ApplyForce(body2, Vector2Scale(direction, force), FM_FORCE);
		}
	}
}
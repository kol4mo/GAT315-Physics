#include "spring.h"
#include "body.h"
#include "mathf.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

ncSpring_t* lllSprings = NULL;

ncSpring_t* CreateSpring(lllBody_t* body1, lllBody_t* body2, float restLength, float k) {
	ncSpring_t* spring = (ncSpring_t*)malloc(sizeof(ncSpring_t));
	assert(spring);

	memset(spring, 0, sizeof(ncSpring_t));
	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->k = k;
	//add element to linked list


	return spring;
}
void AddSpring(ncSpring_t* spring)
{
	assert(spring);

	spring->prev = NULL;
	spring->next = lllSprings;
	if (lllSprings != NULL) {
		lllSprings->prev = spring;
	}
	lllSprings = spring;
}

void DestroySpring(ncSpring_t* spring) {
	assert(spring);
	if (spring->prev) {
		spring->prev->next = spring->next;
	}
	if (spring->next) {
		spring->next->prev = spring->prev;
	}
	if (spring == lllSprings) {
		lllSprings = spring->next;
	}
	free(spring);
}

void DestroyAllSprings() {
	if (!lllSprings) return;

	ncSpring_t* spring = lllSprings;
	while (spring) {
		ncSpring_t* next = spring->next;
		free(spring);
		spring = next;
	}

	lllSprings = NULL;
}

void ApplySpringForce(ncSpring_t* springs) {
	for (ncSpring_t* spring = springs; spring; spring = spring->next)
	{
		//Vector2 direction = <get direction vector from body2 to body1>
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position);
		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);
		float x = length - spring->restLength;
		float force = -spring->k * x;

		Vector2 ndirection = Vector2Normalize(direction);

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}
}
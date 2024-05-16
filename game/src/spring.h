#pragma once

typedef struct ncSpring {
	struct lllBody* body1;
	struct lllBody* body2;
	float restLength;
	float k;

	struct ncSpring* next;
	struct ncSpring* prev;
} ncSpring_t;

extern ncSpring_t* lllSprings;

ncSpring_t* CreateSpring(struct lllBody_t* body1, struct lllBody_t* body2, float restLength, float k);
void AddSpring(ncSpring_t* spring);
void DestroySpring(ncSpring_t* spring);
void DestroyAllSprings();

void ApplySpringForce(ncSpring_t* springs);
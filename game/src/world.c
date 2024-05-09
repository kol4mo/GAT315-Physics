#pragma once
#include "world.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

lllBody* lllBodies = NULL;
int lllBodyCount = 0;
Vector2 lllGravity;

 lllBody* CreateBody(Vector2 position, float mass, lllBodyType bodyType) {
	 lllBody* body = (lllBody*)malloc(sizeof(lllBody));
	 assert(body);

	 memset(body, 0, sizeof(lllBody));
	 body->position = position;
	 body->mass = mass;

	 body->inverseMass = (bodyType == BT_DYNAMIC) ? 1 / mass : 0;
	 body->bodyType = bodyType;
	 //add element to linked list


	 return body;
}
 void AddBody(lllBody* body)
 {
	 assert(body);

	 body->prev = NULL;
	 body->next = lllBodies;
	 if (lllBodies != NULL) {
		 lllBodies->prev = body;
	 }
	 lllBodies = body;
	 lllBodyCount++;
 }

 void DestroyBody(lllBody* body) {
	 assert(body);
	 if (body->prev) {
		 body->prev->next = body->next;
	 }
	 if (body->next) {
		 body->next->prev = body->prev;
	 }
	 if (body == lllBodies) {
		 lllBodies = body->next;
	 }
	 lllBodyCount--;
	 free(body);
}
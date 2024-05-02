#pragma once
#include "world.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

lllBody* lllBodies = NULL;
int lllBodyCount = 0;
Vector2 lllGravity;

 lllBody* CreateBody() {
	 lllBody* body = (lllBody*)malloc(sizeof(lllBody));
	 assert(body);

	 memset(body, 0, sizeof(lllBody));
	 body->prev = NULL;
	 body->next = lllBodies;
	 if (lllBodies) {
		 lllBodies->prev = body;
	 }
	 lllBodies = body;
	 lllBodyCount++;

	 return body;
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
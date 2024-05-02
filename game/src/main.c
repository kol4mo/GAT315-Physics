#include "integrator.h"
#include "body.h"
#include "world.h"
#include "raylib.h"
#include "mathf.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

int main(void)
{
	InitWindow(1280, 720, "particles");
	SetTargetFPS(60);

	//initialize world
	lllGravity = (Vector2){ 0, 30 };

	//game loop
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0)) {
			lllBody* body = CreateBody();
			body->position = position;
			body->mass = GetRandomFloatValue(1, 10);
			body->inverseMass = 1 / body->mass;
			body->bodyType = BT_DYNAMIC;
			body->damping = GetRandomFloatValue01();
			body->gravityScale = 5;
			//ApplyForce(body, CreateVector2(GetRandomFloatValue(-100, 100), GetRandomFloatValue(-100, 100)), FM_VELOCITY);
		}

		//apply foce
		lllBody* body = lllBodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			// update body position
			//ApplyForce(body, lllGravity, FM_FORCE);
			body = body->next; // get next body
		}

		//update Bodies
		body = lllBodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			// update body position
			Step(body, dt);
			body = body->next; // get next body
		}

		//Render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (ms %.2fms)", fps, 1000/fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 10, YELLOW);
		//DrawCircle((int)position.x, (int)position.y, 5, BLACK);
		//DrawCircleLines((int)position.x, (int)position.y, 10, YELLOW);
		//draw bodies
		body = lllBodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			// draw body
			DrawCircle((int)(body->position.x), (int)body->position.y, body->mass, RED);

			body = body->next; // get next body
		}

		EndDrawing();
	}


	CloseWindow();
	free(lllBodies);
	return 0;
}

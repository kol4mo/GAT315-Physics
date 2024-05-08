
#include "integrator.h"
#include "body.h"
#include "world.h"
#include "raylib.h"
#include "mathf.h"
#include "raymath.h"
#include "force.h"
#include "render.h"
#include "editor.h"
#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

int main(void)
{
	InitWindow(1280, 720, "particles");
	InitEditor();
	SetTargetFPS(60);

	//initialize world
	lllGravity = (Vector2){ 0, 0 };
	//game loop
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();

		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);
		UpdateEditor(position);
		if (IsMouseButtonPressed(0)) {
			Color* fireworkColor = (Color*)malloc(sizeof(Color));
			fireworkColor->r = GetRandomFloatValue(0, 255);
			fireworkColor->g = GetRandomFloatValue(0, 255);
			fireworkColor->b = GetRandomFloatValue(0, 255);
			fireworkColor->a = 255;
			Vector2 angle = getVector2FromAngle(GetRandomFloatValue(0, 360) * DEG2RAD);
			for (int i = 0; i < 1; i++)
			{
				lllBody* body = CreateBody();
				body->position = ConvertScreenToWorld(position);
				body->mass = GetRandomFloatValue(nceditorData.MassMinValue, nceditorData.MassMaxValue);
				body->inverseMass = 1 / body->mass;
				body->bodyType = BT_DYNAMIC;
				body->damping = 0;
				body->gravityScale = 5;
				body->color = fireworkColor;

				//ApplyForce(body, Vector2Scale(angle, GetRandomFloatValue(-2, 2)), FM_IMPULSE);
			}
		}

		//apply foce
		ApplyGravitation(lllBodies, nceditorData.GravitationValue);
		

		//update Bodies
		for (lllBody* body = lllBodies; body; body = body->next) {
			Step(body, dt);
		}


		//Render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (ms %.2fms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 10, YELLOW);
		//DrawCircle((int)position.x, (int)position.y, 5, BLACK);
		//DrawCircleLines((int)position.x, (int)position.y, 10, YELLOW);
		//draw bodies
		for (lllBody* body = lllBodies; body; body = body->next) { // do while we have a valid pointer, will be NULL at the end of the list
			// draw body
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)(screen.x), (int)screen.y, ConvertWorldToPixel(body->mass), *body->color);

			// get next body
		}
		DrawEditor();

		EndDrawing();
	}


	CloseWindow();
	free(lllBodies);
	return 0;
}

#pragma once
#include "body.h"
#include "raylib.h"
#include "mathf.h"
#include "raymath.h"
#include "world.h"
#include "integrator.h"
#include "force.h"
#include "render.h"
#include "editor.h"
#include "spring.h"
#include "collision.h"
#include "contact.h"
#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10000

#define MAX_POINTS 20

int main(void)
{

	lllBody_t* selectedBody = NULL;
	lllBody_t* connectBody = NULL;

	InitWindow(1280, 720, "particles");
	InitEditor();
	HideCursor();
	SetTargetFPS(60);

	//initialize world
	//lllGravity = (Vector2){ 0, 0 };
	//game loop
	while (!WindowShouldClose())
	{
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		lllGravity = (Vector2){ 0 , -nceditorData.GravitationValue };
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);
		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		UpdateEditor(position);
		selectedBody = getBodyIntersect(lllBodies, position);
		if (selectedBody) {
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines(screen.x, screen.y, ConvertWorldToPixel(selectedBody->mass * 0.5f) + 5, RED);
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))) {
			Color* fireworkColor = (Color*)malloc(sizeof(Color));
			fireworkColor->r = GetRandomFloatValue(0, 255);
			fireworkColor->g = GetRandomFloatValue(0, 255);
			fireworkColor->b = GetRandomFloatValue(0, 255);
			fireworkColor->a = 255;
			Vector2 angle = getVector2FromAngle(GetRandomFloatValue(0, 360) * DEG2RAD);
			for (int i = 0; i < 1; i++)
			{
				lllBody_t* body = CreateBody(ConvertScreenToWorld(position), nceditorData.MassMinValue, nceditorData.BodyTypeActive);
				body->damping = nceditorData.Damping;
				body->gravityScale = 5;
				body->color = fireworkColor;
				body->restitution = 0.8f;

				AddBody(body);
				//ApplyForce(body, Vector2Scale(angle, GetRandomFloatValue(-2, 2)), FM_IMPULSE);
			}
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) connectBody = selectedBody;
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) DrawLineBodyToPosition(connectBody, position);
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody) {
			if (selectedBody && selectedBody != connectBody) {
				ncSpring_t* spring = CreateSpring(connectBody, selectedBody, Vector2Distance(connectBody->position, selectedBody->position) / 2, 20);
				AddSpring(spring);
			}
		}

		//apply foce
		//ApplyGravitation(lllBodies, nceditorData.GravitationValue);
		ApplySpringForce(lllSprings);

		//update Bodies
		for (lllBody_t* body = lllBodies; body; body = body->next) {
			Step(body, dt);
		}

		ncContact_t* contacts = NULL;
		CreateContacts(lllBodies, &contacts);
		SeparateContacts(contacts);
		ResolveContacts(contacts);
		
		//Render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (ms %.2fms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("FRAME: %.4f", dt), 10, 30, 20, LIME);

		//DrawCircle((int)position.x, (int)position.y, 5, BLACK);
		//DrawCircleLines((int)position.x, (int)position.y, 10, YELLOW);
		for (ncSpring_t* spring = lllSprings; spring; spring = spring->next) {
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine((int)screen1.x, (int)screen1.y, (int)screen2.x, (int)screen2.y, RED);
		}
		//draw bodies
		for (lllBody_t* body = lllBodies; body; body = body->next) { // do while we have a valid pointer, will be NULL at the end of the list
			// draw body
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)(screen.x), (int)screen.y, ConvertWorldToPixel(body->mass * 0.5f), *body->color);

			// get next body
		}

		for (ncContact_t* contact = contacts; contact; contact = contact->next) { // do while we have a valid pointer, will be NULL at the end of the list
			// draw body
			
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircle((int)(screen.x), (int)screen.y, ConvertWorldToPixel(contact->body1->mass * 0.5f), RED);

			// get next body
		}
		DrawEditor(position);

		EndDrawing();
	}


	CloseWindow();
	free(lllBodies);
	return 0;
}

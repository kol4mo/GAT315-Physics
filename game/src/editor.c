#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"
#include "body.h"
#include "render.h"

#define EDITOR_DATA(data) TextFormat("%0.2f", data), &data

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
ncEditorData_t nceditorData;
Vector2 anchor01 = { 1000, 8 };
Vector2 anchor02 = { 1000, 358 };
Texture2D cursorTexture;

bool BodyBoxActive = true;
bool WorldBoxActive = true;

void InitEditor()
{
	GuiLoadStyle("raygui/styles/candy/style_candy.rgs");

	Image image = LoadImage("resources/Reticle.png");
	cursorTexture = LoadTextureFromImage(image);
	UnloadImage(image);
	BodyBoxActive = true;
	WorldBoxActive = true;
	nceditorData.simulateToggle = true;
	nceditorData.resetButton = false;
	nceditorData.MassMinValue = 4.0;
	nceditorData.MassMaxValue = 7.0;
	nceditorData.GravitationValue = 0;
	nceditorData.BodyTypeEditMode = false;
	nceditorData.BodyTypeActive = 0;
	nceditorData.GravityValue = 0;
	nceditorData.Damping = 0;
	nceditorData.TimeStep = 50;
	nceditorData.GravityScale = 1.0f;
	nceditorData.Stiffness = 10.0f;
	nceditorData.Restitution = 0.4f;
}

void UpdateEditor(Vector2 position)
{
}

void DrawEditor(Vector2 position)
{
	if (BodyBoxActive)
	{
		BodyBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 320, 325 }, "Body");
		GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 32, 120, 16 }, "Mass", EDITOR_DATA(nceditorData.MassMinValue), 0.1f, 40);
		GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 64, 120, 16 }, "Damping", EDITOR_DATA(nceditorData.Damping), 0, 100);
		GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 96, 120, 16 }, "Gravity Scale", EDITOR_DATA(nceditorData.GravityScale), 0, 20);
		GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 128, 120, 16 }, "Stiffness (k)", EDITOR_DATA(nceditorData.Stiffness), 0, 50);
		GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 160, 120, 16 }, "Restitution", EDITOR_DATA(nceditorData.Restitution), 0, 1);
		if (GuiDropdownBox((Rectangle) { anchor01.x + 96, anchor01.y + 244, 120, 24 }, "Static;Kinematic;Dynamic", & nceditorData.BodyTypeActive, nceditorData.BodyTypeEditMode)) nceditorData.BodyTypeEditMode = !nceditorData.BodyTypeEditMode;
	}
	if (WorldBoxActive) {
		WorldBoxActive = !GuiWindowBox((Rectangle) { anchor02.x + 0, anchor02.y + 0, 320, 325 }, "World");
		GuiSliderBar((Rectangle) { anchor02.x + 96, anchor02.y + 32, 120, 16 }, "Gravity", EDITOR_DATA(nceditorData.GravityValue), -50, 50);
		GuiSliderBar((Rectangle) { anchor02.x + 96, anchor02.y + 64, 120, 16 }, "Gravitation", EDITOR_DATA(nceditorData.GravitationValue), 0, 100);
		GuiSliderBar((Rectangle) { anchor02.x + 96, anchor02.y + 96, 120, 16 }, "TimeStep", EDITOR_DATA(nceditorData.TimeStep), 0.01f, 100); 
		GuiToggle((Rectangle) { anchor02.x + 150, anchor02.y + 224, 88, 24 }, "Simulate", &nceditorData.simulateToggle);

		nceditorData.resetButton = GuiButton((Rectangle) { anchor02.x + 48, anchor02.y + 224, 88, 24 }, "Reset");
	}
	DrawTexture(cursorTexture, (int)position.x - (cursorTexture.width / 2), position.y - (cursorTexture.height/2), WHITE);
	GuiUnlock();
}

struct lllBody_t* getBodyIntersect(lllBody_t* bodies, Vector2 position)
{
	for (lllBody_t* body = bodies; body; body = body->next)
	{
		Vector2 screen = ConvertWorldToScreen(body->position);
		if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass)))
		{
			return body;
		}
	}

	return NULL;
}

void DrawLineBodyToPosition(lllBody_t* body, Vector2 position)
{
	Vector2 screen = ConvertWorldToScreen(body->position);
	DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}
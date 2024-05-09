#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
ncEditorData_t nceditorData;
Vector2 anchor01 = { 1000, 8 };
Texture2D cursorTexture;

bool EditorBoxActive = true;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/candy/style_candy.rgs");

    Image image = LoadImage("resources/Reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    EditorBoxActive = true;
    nceditorData.MassMinValue = 0.1f;
    nceditorData.MassMaxValue = 0.0f;
    nceditorData.GravitationValue = 0.0f;
    nceditorData.BodyTypeEditMode = false;
    nceditorData.BodyTypeActive = 0;
    nceditorData.GravityValue = 0.0f;
    nceditorData.SliderBar007Value = 0.0f;
}

void UpdateEditor(Vector2 position)
{
}

void DrawEditor(Vector2 position)
{
        if (EditorBoxActive)
        {
            EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 320, 656 }, "Editor");
            GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 32, 120, 16 }, "Mass Min", NULL, &nceditorData.MassMinValue, 0.1f, 100);
            GuiSliderBar((Rectangle) {anchor01.x + 96, anchor01.y + 72, 120, 16 }, "Mass Max", NULL, & nceditorData.MassMaxValue, 0, 100);
            GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 112, 120, 16 }, "Gravitation", NULL, & nceditorData.GravitationValue, 0, 100);
            GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 248, 120, 16 }, "Damping", NULL, & nceditorData.GravityValue, 0, 100);
            GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 208, 120, 16 }, "Gravity", NULL, & nceditorData.SliderBar007Value, 0, 100);
            if (GuiDropdownBox((Rectangle) { anchor01.x + 96, anchor01.y + 144, 120, 24 }, "Static;Kinematic;Dynamic", & nceditorData.BodyTypeActive, nceditorData.BodyTypeEditMode)) nceditorData.BodyTypeEditMode = !nceditorData.BodyTypeEditMode;
        }
        DrawTexture(cursorTexture, position.x, position.y, WHITE);
            GuiUnlock();
}

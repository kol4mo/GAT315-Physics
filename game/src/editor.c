#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
ncEditorData_t nceditorData;
Vector2 anchor01 = { 1000, 8 };

bool EditorBoxActive = true;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/candy/style_candy.rgs");
    nceditorData.MassMaxValue = 1;
    nceditorData.MassMinValue = 0.1f;
    nceditorData.GravitationValue = 2;
}

void UpdateEditor(Vector2 position)
{
}

void DrawEditor()
{
    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 320, 656 }, "Editor");
        GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 32, 120, 16 }, "Mass Min", NULL, &nceditorData.MassMinValue, 0.01f, 10);
        GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 72, 120, 16 }, "Mass Max", NULL, &nceditorData.MassMaxValue, 0.01f, 10);
        GuiSliderBar((Rectangle) { anchor01.x + 96, anchor01.y + 112, 120, 16 }, "Gravitation", NULL, &nceditorData.GravitationValue, 0, 100);
    }
}

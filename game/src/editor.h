#pragma once
#include "raylib.h"

typedef struct ncEditorData {
    float MassMinValue;
    float MassMaxValue;
    float GravitationValue;
    bool BodyTypeEditMode;
    int BodyTypeActive;
    float GravityValue;
    float SliderBar007Value;
}ncEditorData_t;

extern ncEditorData_t nceditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor(Vector2 position);
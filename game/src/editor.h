#pragma once
#include "raylib.h"


typedef struct ncEditorData {
    float MassMinValue;
    float MassMaxValue;
    float GravitationValue;
    bool BodyTypeEditMode;
    int BodyTypeActive;
    float GravityValue;
    float Damping;
    float TimeStep;
    float GravityScale;
    float Stiffness;
    float Restitution;
    bool simulateToggle;
    bool resetButton;
}ncEditorData_t;

extern ncEditorData_t nceditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor(Vector2 position);

struct lllBody_t* getBodyIntersect(struct lllBody_t* bodies, Vector2 position);

void DrawLineBodyToPosition(struct lllBody_t* body, Vector2 position);
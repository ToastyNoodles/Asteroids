#pragma once
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

void DrawLines(Vector2* points, int sizeOfPoints, Vector2 position, float rotation, float scale);
void DrawLines(Vector2* points, int sizeOfPoints, Vector2 position, float rotation, float scale, Color color);
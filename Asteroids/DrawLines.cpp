#include "DrawLines.hpp"

void DrawLines(Vector2* points, int sizeOfPoints, Vector2 position, float rotation, float scale)
{
	for (int point = 0; point < sizeOfPoints; point++)
	{
		rlPushMatrix();
		rlTranslatef(position.x, position.y, 0);
		rlRotatef(-rotation, 0, 0, -1);
		if (point != sizeOfPoints - 1)
		{
			DrawLineEx(Vector2Multiply(points[point], Vector2{ scale, scale }), Vector2Multiply(points[point + 1], Vector2{ scale, scale }), 1.0f, WHITE);
		}
		else
		{
			DrawLineEx(Vector2Multiply(points[point], Vector2{ scale, scale }), Vector2Multiply(points[0], Vector2{ scale, scale }), 1.0f, WHITE);
		}
		rlPopMatrix();
	}
}

void DrawLines(Vector2* points, int sizeOfPoints, Vector2 position, float rotation, float scale, Color color)
{
	for (int point = 0; point < sizeOfPoints; point++)
	{
		rlPushMatrix();
		rlTranslatef(position.x, position.y, 0);
		rlRotatef(-rotation, 0, 0, -1);
		if (point != sizeOfPoints - 1)
		{
			DrawLineEx(Vector2Multiply(points[point], Vector2{ scale, scale }), Vector2Multiply(points[point + 1], Vector2{ scale, scale }), 1.0f, color);
		}
		else
		{
			DrawLineEx(Vector2Multiply(points[point], Vector2{ scale, scale }), Vector2Multiply(points[0], Vector2{ scale, scale }), 1.0f, color);
		}
		rlPopMatrix();
	}
}
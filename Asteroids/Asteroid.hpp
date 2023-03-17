#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "DrawLines.hpp"

class Asteroid
{
public:
	Asteroid(Vector2 spawnPosition, bool spawnRandom, bool randomSize, float size);
	void UpdateAsteroid();
	void DrawAsteroid();

	void SetHasCollided(bool value) { hasCollided = value; }
	bool GetHasCollided() { return hasCollided; }

	Vector2 GetPosition() { return position; }
	Vector2 GetForward() { return forward; }
	Vector2* GetPoints() { return points; }
	Vector2 GetScale() { return Vector2{ scale, scale }; }
	float GetRotation() { return rotation; }
	int GetLengthOfPoints() { return sizeof(points) / sizeof(Vector2); }
private:
	Vector2 position;
	Vector2 velocity;
	Vector2 forward;
	float rotation;
	float speed;
	float scale;
	bool hasCollided;

	Vector2 points[7] =
	{
		Vector2{  0.20f, -1.00f },
		Vector2{  1.00f, -0.50f },
		Vector2{  1.00f,  0.40f },
		Vector2{  0.60f,  1.00f },
		Vector2{ -0.20f,  0.60f },
		Vector2{ -0.80f,  0.40f },
		Vector2{ -0.85f, -0.65f }
	};
};
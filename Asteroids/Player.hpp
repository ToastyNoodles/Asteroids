#pragma once
#include <raylib.h>
#include <raymath.h>
#include "DrawLines.hpp"

class Player
{
public:
	void SpawnPlayer();
	void UpdatePlayer();
	void DrawPlayer();

	Vector2 GetPosition() { return position; }
	Vector2 GetForward() { return forward; }
private:
	Vector2 position;
	Vector2 velocity;
	Vector2 forward;
	float rotation;
	float speed;
	float friction;
	float scale;

	Vector2 points[3] =
	{
		Vector2{  0.5f,  0.0f },
		Vector2{ -0.25f,  0.25f },
		Vector2{ -0.25f, -0.25f }
	};

	void PlayerInput();
};
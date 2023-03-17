#include <raylib.h>
#include "GameManager.hpp"

int windowWidth = 800;
int windowHeight = 800;

Camera2D camera;
GameManager game;

int main()
{
	InitWindow(windowWidth, windowHeight, "Asteroids");

	camera.offset = Vector2{ windowWidth / 2.0f, windowHeight / 2.0f };
	camera.target = Vector2{ 0.0f, 0.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	game.StartGame();
	while (!WindowShouldClose())
	{
		ClearBackground(BLACK);

		game.UpdateGame();

		BeginDrawing();
		BeginMode2D(camera);

		game.DrawGame();
		game.UpdateCollisions();

		EndMode2D();

		game.DrawScreen();

		EndDrawing();
	}

	return 0;
}
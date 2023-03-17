#include "Asteroid.hpp"

Asteroid::Asteroid(Vector2 spawnPosition, bool spawnRandom, bool randomSize, float size)
{
	position = (!spawnRandom) ? spawnPosition : Vector2{ (float)GetRandomValue(-400, 400), (float)GetRandomValue(-400, 400) };
	rotation = (float)GetRandomValue(0, 360);
	speed = (float)(rand()) / (float)(RAND_MAX) + 0.2f;
	forward = Vector2{ (float)cos(DEG2RAD * rotation), (float)sin(DEG2RAD * rotation) };
	velocity.x = forward.x * speed;
	velocity.y = forward.y * speed;
	scale = (!randomSize) ? size : (int)GetRandomValue(35, 70);
	hasCollided = false;

void Asteroid::UpdateAsteroid()
{
	position.x += velocity.x;
	position.y += velocity.y;

	if (position.x > 400) { position.x = -400; }
	if (position.x < -400) { position.x = 400; }
	if (position.y > 400) { position.y = -400; }
	if (position.y < -400) { position.y = 400; }
}

void Asteroid::DrawAsteroid()
{
	DrawLines(points, sizeof(points) / sizeof(Vector2), position, rotation, scale);
}
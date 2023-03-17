#include "Projectile.hpp"

Projectile::Projectile(Vector2 spawnPosition, Vector2 direction)
{
	speed = 10.0f;
	lifeTime = 0.5f;
	position = Vector2Add(spawnPosition, Vector2Multiply(direction, Vector2{ 28.0f, 28.0f }));
	velocity.x = direction.x * speed;
	velocity.y = direction.y * speed;
	predicted = Vector2{ 0.0f, 0.0f };
	hasCollided = false;
}

void Projectile::UpdateProjectile()
{
	position.x += velocity.x;
	position.y += velocity.y;

	if (position.x > 400) { position.x = -400; }
	if (position.x < -400) { position.x = 400; }
	if (position.y > 400) { position.y = -400; }
	if (position.y < -400) { position.y = 400; }

	lifeTime -= 1.0f * GetFrameTime();
}

void Projectile::DrawProjectile()
{
	DrawCircle((int)position.x, (int)position.y, 1.0f, WHITE);
	//DrawLineEx(position, Vector2Add(position, velocity), 1.0f, RED);
}
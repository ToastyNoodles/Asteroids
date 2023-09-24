#include "Player.hpp"

void Player::SpawnPlayer()
{
	position = Vector2{ 0.0f, 0.0f };
	velocity = Vector2{ 0.0f, 0.0f };
	forward = Vector2{ 0.0f, 0.0f };
	rotation = -90.0f;
	speed = 2.0f;
	friction = 0.3f;
	scale = 50.0f;
	hasCollided = false;
}

void Player::UpdatePlayer()
{
	PlayerInput();

	forward = Vector2{ (float)cos(DEG2RAD * rotation), (float)sin(DEG2RAD * rotation) };

	if (rotation >= 360 || rotation <= -360) { rotation = 0.0f; }

	if ( position.x > 400) {  position.x = -400; }
	if ( position.x < -400) {  position.x = 400; }
	if ( position.y > 400) {  position.y = -400; }
	if ( position.y < -400) {  position.y = 400; }

	position.x += velocity.x;
	position.y += velocity.y;
	if ( velocity.x != 0) { velocity.x += -velocity.x * (GetFrameTime() * friction); }
	if ( velocity.y != 0) { velocity.y += -velocity.y * (GetFrameTime() * friction); }
}

void Player::DrawPlayer()
{
	DrawLines(points, sizeof(points) / sizeof(Vector2), position, rotation, scale);
}

void Player::PlayerInput()
{
	if (!hasCollided)
	{
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
		{
			rotation -= 1.0f;
		}
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
		{
			rotation += 1.0f;
		}
		if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
		{
			velocity.x += forward.x * (GetFrameTime() * speed);
			velocity.y += forward.y * (GetFrameTime() * speed);
		}
	}
}
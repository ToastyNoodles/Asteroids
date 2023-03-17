#pragma once
#include <raylib.h>
#include <raymath.h>

class Projectile
{
public:
	Projectile(Vector2 position, Vector2 forward);
	void UpdateProjectile();
	void DrawProjectile();
	
	void SetHasCollided(bool value) { hasCollided = value; }
	bool GetHasCollided() { return hasCollided; }

	Vector2 GetPosition() { return position; }
	Vector2 GetVelocity() { return velocity; }
	float GetLifeTime() { return lifeTime; }
private:
	Vector2 position;
	Vector2 velocity;
	Vector2 predicted;
	float speed;
	float lifeTime;
	bool hasCollided;
};
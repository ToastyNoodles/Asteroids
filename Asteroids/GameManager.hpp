#pragma once
#include <vector>
#include "Player.hpp"
#include "Projectile.hpp"
#include "Asteroid.hpp"

class GameManager
{
public:
	void StartGame();
	void UpdateGame();
	void UpdateCollisions();
	void DrawGame();
	void DrawScreen();

	void SetScore(int score) { score = score; }
	int GetScore() { return score; }
private:
	Font font;
	int score = 0;

	Player player;
	std::vector<Projectile*> projectiles;
	std::vector<Asteroid*> asteroids;

	void SpawnAsteroids(int amount, Vector2 position, bool randomSpawns, bool randomSize, float size);
	void ReloadGame();
};
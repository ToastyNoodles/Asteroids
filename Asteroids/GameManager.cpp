#include "GameManager.hpp"
#include <string>

void GameManager::StartGame()
{
	font = LoadFont("res/PressStart2P.ttf");
	player.SpawnPlayer();

	SpawnAsteroids(6, Vector2{ 0.0f, 0.0f }, true, true, 0.0f);
}

void GameManager::UpdateGame()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		projectiles.push_back(new Projectile(player.GetPosition(), player.GetForward()));
	}
	if (IsKeyPressed(KEY_R))
	{
		ReloadGame();
	}

	player.UpdatePlayer();
	if (asteroids.size() <= 5)
	{
		SpawnAsteroids(2, Vector2{ 400.0f, 400.0f }, false, true, 0.0f);
	}
	for (int projectile = 0; projectile < projectiles.size(); projectile++)
	{
		projectiles[projectile]->UpdateProjectile();
		if (projectiles[projectile]->GetLifeTime() <= 0)
		{
			projectiles.erase(projectiles.begin() + projectile);
		}
	}
	for (int asteroid = 0; asteroid < asteroids.size(); asteroid++)
	{
		asteroids[asteroid]->UpdateAsteroid();
	}
}

void GameManager::DrawGame()
{
	player.DrawPlayer();
	for (int projectile = 0; projectile < projectiles.size(); projectile++)
	{
		projectiles[projectile]->DrawProjectile();
	}
	for (int asteroid = 0; asteroid < asteroids.size(); asteroid++)
	{
		asteroids[asteroid]->DrawAsteroid();
	}
}

void GameManager::DrawScreen()
{
	std::string ScoreText = "Score: " + std::to_string(score);
	DrawTextEx(font, ScoreText.c_str(), Vector2{ 400.0f - MeasureText(ScoreText.c_str(), 20), 15 }, 20, 1, WHITE);

	/*std::string SpawnInfoText = "Spawned Projectiles: " + std::to_string(projectiles.size()) + " | Spawned Asteroids: " + std::to_string(asteroids.size()) + " | R - Reload Game";
	DrawTextEx(font, SpawnInfoText.c_str(), Vector2{ 5, 800 - 15 }, 8, 1, WHITE);*/
}

void GameManager::UpdateCollisions()
{
	for (int projectile = 0; projectile < projectiles.size(); projectile++)
	{
		if (projectiles[projectile]->GetHasCollided()) { continue; }
		for (int asteroid = 0; asteroid < asteroids.size(); asteroid++)
		{
			for (int point = 0; point < asteroids[asteroid]->GetLengthOfPoints(); point++)
			{
				if (point != asteroids[asteroid]->GetLengthOfPoints() - 1)
				{
					if (CheckCollisionLines(projectiles[projectile]->GetPosition(), Vector2Add(projectiles[projectile]->GetPosition(), projectiles[projectile]->GetVelocity()), Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[point], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition()), Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[point + 1], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition()), nullptr))
					{
						projectiles[projectile]->SetHasCollided(true);
						asteroids[asteroid]->SetHasCollided(true);
					}
				}
				else
				{
					if (CheckCollisionLines(projectiles[projectile]->GetPosition(), Vector2Add(projectiles[projectile]->GetPosition(), projectiles[projectile]->GetVelocity()), Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[point], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition()), Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[0], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition()), nullptr))
					{
						projectiles[projectile]->SetHasCollided(true);
						asteroids[asteroid]->SetHasCollided(true);
					}
				}
			}
		}
	}

	for (int projectile = 0; projectile < projectiles.size(); projectile++)
	{
		if (projectiles[projectile]->GetHasCollided()) 
		{ 
			projectiles.erase(projectiles.begin() + projectile);
		}
	}
	for (int asteroid = 0; asteroid < asteroids.size(); asteroid++)
	{
		if (asteroids[asteroid]->GetHasCollided()) 
		{ 
			float nextSize = asteroids[asteroid]->GetScale().x / 2.0f;
			if (nextSize >= 15)
				SpawnAsteroids(3, asteroids[asteroid]->GetPosition(), false, false, nextSize);

			score += 100;
			asteroids.erase(asteroids.begin() + asteroid);
		}
	}
}

void GameManager::SpawnAsteroids(int amount, Vector2 position, bool randomSpawns, bool randomSize, float size)
{
	for (int i = 0; i < amount; i++)
	{
		asteroids.push_back(new Asteroid(position, randomSpawns, randomSize, size));
	}
}

void GameManager::ReloadGame()
{
	score = 0;
	projectiles.clear();
	asteroids.clear();
	StartGame();
}
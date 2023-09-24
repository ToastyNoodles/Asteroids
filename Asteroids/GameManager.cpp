#include "GameManager.hpp"
#include <string>

void GameManager::StartGame()
{
	if (!haveAssetsBeenLoaded)
	{
		font = LoadFont("res/PressStart2P.ttf");
		haveAssetsBeenLoaded = true;
	}

	player.SpawnPlayer();
	SpawnAsteroids(6, Vector2{ 400.0f, 400.0f }, true, true, 0.0f);
}

void GameManager::UpdateGame()
{
	if (!gameOver)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			projectiles.push_back(new Projectile(player.GetPosition(), player.GetForward()));
		}
	}
	
	if (IsKeyPressed(KEY_R))
	{
		ReloadGame();
	}
	if (IsKeyPressed(KEY_I))
	{
		showDebug = !showDebug;
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

	if (gameOver)
	{
		std::string GameOverText = "GAMEOVER";
		DrawTextEx(font, GameOverText.c_str(), Vector2{ 400.0f - MeasureText(GameOverText.c_str(), 16), 400.0f }, 20, 1, WHITE);
	}

	if (showDebug)
	{
		std::string SpawnInfoText = "Projectiles: " + std::to_string(projectiles.size()) + " | Asteroids: " + std::to_string(asteroids.size()) + " | GameOver: " + std::to_string((int)gameOver) + " | Player: " + std::to_string((int)player.GetPosition().x) + ", " + std::to_string((int)player.GetPosition().y);
		DrawTextEx(font, SpawnInfoText.c_str(), Vector2{ 5, 800 - 15 }, 8, 1, WHITE);
	}
}

void GameManager::UpdateCollisions()
{
	//asteroid - projectile collision check.
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

	//asteroid - player collision check.
	if (!player.GetHasCollided())
	{
		for (int asteroid = 0; asteroid < asteroids.size(); asteroid++)
		{
			Vector2 asteroidVertexToWorld[7] = { 0 };
			for (int asteroidPoint = 0; asteroidPoint < asteroids[asteroid]->GetLengthOfPoints(); asteroidPoint++)
			{
				asteroidVertexToWorld[asteroidPoint] = Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[asteroidPoint], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition());
			}

			//Works when the given position is inside the polygon but sometimes it will say it collided with an asteroid to its right that its not colliding with
			if (CheckCollisionPointPoly(player.GetPosition(), asteroidVertexToWorld, sizeof(asteroidVertexToWorld) / sizeof(Vector2)))
			{
				player.SetHasCollided(true);
				asteroids[asteroid]->SetHasCollided(true);
				gameOver = true;
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
				SpawnAsteroids(2, asteroids[asteroid]->GetPosition(), false, false, nextSize);

			score += 2 * (int)asteroids[asteroid]->GetScale().x;
			asteroids.erase(asteroids.begin() + asteroid);
		}
	}
}

void GameManager::DebugDrawCollisions()
{
	if (!showDebug) { return; }

	for (int projectile = 0; projectile < projectiles.size(); projectile++)
	{
		DrawLineEx(projectiles[projectile]->GetPosition(), Vector2Add(projectiles[projectile]->GetPosition(), projectiles[projectile]->GetVelocity()), 1.0f, DARKGREEN);
	}

	if (!player.GetHasCollided())
	{
		DrawCircleV(player.GetPosition(), 2.0f, DARKGREEN);
	}

	for (int asteroid = 0; asteroid < asteroids.size(); asteroid++)
	{
		if (!asteroids[asteroid]->GetHasCollided())
		{
			for (int point = 0; point < asteroids[asteroid]->GetLengthOfPoints(); point++)
			{
				if (point != asteroids[asteroid]->GetLengthOfPoints() - 1)
				{
					DrawLineEx(Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[point], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition()), Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[point + 1], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition()), 2.0f, DARKGREEN);
				}
				else
				{
					DrawLineEx(Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[point], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition()), Vector2Add(Vector2Multiply(asteroids[asteroid]->GetPoints()[0], asteroids[asteroid]->GetScale()), asteroids[asteroid]->GetPosition()), 2.0f, DARKGREEN);
				}
			}
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
	gameOver = false;
	StartGame();
}
#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	currentSpawnTimer = 300;
	spawnTimer = 300; // Spawn time of 5 secs

		spawn();
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		currentSpawnTimer = spawnTimer;
		spawn();
	}

	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i] ->getPositionX() < 0)
		{
			// Cache the variable so we can delete it later
			Enemy* enemyToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemyToErase;

			break;
		}
	}
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1300, 400 + (rand() % 400));
	spawnedEnemies.push_back(enemy);
}

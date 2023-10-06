#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor

	player = new Player();
	this->addGameObject(player);

	points = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();

	background = loadTexture("gfx/background.png");

	// Initialize any scene logic here

	initFonts();

	currentSpawnTimer = 300;
	spawnTimer = 300; // Spawn time of 5 secs

	spawn();
}

void GameScene::draw()
{
	//draw texture

	int Height = 1000;
	int Width = 700;

	blit(background, 0, 0);

	blitScale(background, 0, 0, &Width, &Height, 3);

	Scene::draw();

	drawText(100, 20, 225, 225, 225, TEXT_CENTER, "SCORE: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5, 225, 225, 225, TEXT_CENTER, "GAME OVER!");
	}

}

void GameScene::update()
{
	Scene::update();

	doSpawnLogin();
	doCollisionLogic();
	
	for (int i = 0; i < objects.size(); i++)
	{
		Explosion* Explosions = dynamic_cast<Explosion*>(objects[i]);

		if (Explosions != NULL)
		{
			if (Explosions->getTime() <= 0)
			{
				Explosion* explosionsDone = Explosions;
				explosions.erase(explosions.begin());
				delete explosionsDone;
			}
		}
	}
}

void GameScene::doSpawnLogin()
{
	if (currentSpawnTimer > 0)
		currentSpawnTimer--;

	if (currentSpawnTimer <= 0)
	{
		currentSpawnTimer = spawnTimer;
		spawn();
	}
}

void GameScene::doCollisionLogic()
{
	
	//Checking for collisions
	for (int i = 0; i < objects.size(); i++)
	{
		//Cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		//Check if the cast was successful
		if (bullet != NULL)
		{
			// If bullet is from enemy side, check against player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					player->doDeath();
					break;
				}
			}

			// If bullet is from player side, check against ALL enemies
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						explosion(currentEnemy);
						despawnEnemy(currentEnemy);

						//IMPORTANT : delete one only
						// if not it will crash bcs of looping 

						// Increment points
						points++;

						break;
					}
				}
			}
		}

		for (int i = 0; i < spawnedEnemies.size(); i++)
		{
			if (spawnedEnemies[i]->getPositionX() < 0)
			{
				// Cache the variable so we can delete it later
				Enemy* enemyToErase = spawnedEnemies[i];
				spawnedEnemies.erase(spawnedEnemies.begin() + i);
				delete enemyToErase;

				break;
			}
		}
	}
}

void GameScene::explosion(Enemy* enemy)
{
	Explosion* explosion = new Explosion(enemy->getPositionX(), enemy->getPositionY(), enemy->getWidth(), enemy->getHeight());

	this->addGameObject(explosion);
	explosions.push_back(explosion);
}

void GameScene::spawn()
{
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1300, 400 + (rand() % 400));
	spawnedEnemies.push_back(enemy);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		// If the pointer matches
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	// If any match is found
	if (index != -1)
	{
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}
#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Snake();
	this->addGameObject(player);
}

GameScene::~GameScene()
{
}

void GameScene::start()
{
	Scene::start();
	spawnFruit();

	// Initialize any scene logic here
	screenWidth = 660;
	screenHeight = 660;
	background = loadTexture("gfx/background.png");

	fruitSpawnInterval = 30;
}

void GameScene::draw()
{
	Scene::draw();

	blit(background, 0, 0);
	blitScale(background, 0, 0, &screenWidth, &screenHeight, 0);

	if (!spawnedFruit.empty())
	{
		newFruit = spawnedFruit[0];
		newFruit->draw();
	}

	player->draw();
}

void GameScene::update()
{
	Scene::update();

	if (player->getPositionX() < 30 || player->getPositionX() > 600 || player->getPositionY() < 30 || player->getPositionY() > 600)
	{
		player->doDeath();
	}
}

void GameScene::spawnFruit()
{
	if (spawnedFruit.empty())
	{
		Fruit* anotherfruit = new Fruit();
		this->addGameObject(anotherfruit);
		spawnedFruit.push_back(anotherfruit);
	}
}

void GameScene::checkCollision()
{
}

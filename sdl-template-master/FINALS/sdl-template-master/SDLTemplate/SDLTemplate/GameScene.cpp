#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	snake = new Snake();
	this->addGameObject(snake);
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
	bodyInterval = 30;
}

void GameScene::draw()
{
	Scene::draw();

	blit(background, 0, 0);
	blitScale(background, 0, 0, &screenWidth, &screenHeight, 0);

	if (!spawnedFruit.empty())
	{
		newFruit = spawnedFruit[0];
		if (newFruit)
		{
			newFruit->draw();
		}
	}

	snake->draw();

	for (int i = 0; i < bodySegments.size(); i++)
	{
		bodySegments[i]->draw();
	}
}

void GameScene::update()
{
	Scene::update();

	if (snake->getPositionX() < 30 || snake->getPositionX() > 600 || snake->getPositionY() < 30 || snake->getPositionY() > 600)
	{
		snake->doDeath();
	}

	for (int i = bodySegments.size() - 1; i > 0; --i)
	{
		bodySegments[i]->setPosition(bodySegments[i - 1]->getPositionX(), bodySegments[i - 1]->getPositionY());
	}

	if (bodySegments.size() > 0)
	{
		bodySegments[0]->setPosition(snake->getPreviousPositionX(), snake->getPreviousPositionY());
	}

	checkCollisionFruit();
	checkCollisionBody();

	snake->update();
}

void GameScene::spawnFruit()
{
	Fruit* anotherFruit = new Fruit();
	this->addGameObject(anotherFruit);
	spawnedFruit.push_back(anotherFruit);
}

void GameScene::despawnFruit()
{
	if (!spawnedFruit.empty())
	{
		delete spawnedFruit[0];
		spawnedFruit.erase(spawnedFruit.begin());
	}
}

void GameScene::checkCollisionFruit()
{
	if (!spawnedFruit.empty())
	{
		Fruit* currentFruit = spawnedFruit[0];
		if (snake->getPositionX() == currentFruit->getPositionX() && snake->getPositionY() == currentFruit->getPositionY())
		{
			spawnFruit(); 
			spawnBodySegment();
			delete currentFruit;  
			spawnedFruit.erase(spawnedFruit.begin());  
		}
	}
}

void GameScene::checkCollisionBody()
{
	for (int i = 0; i < bodySegments.size(); i ++)
	{
		if (snake->getPositionX() == bodySegments[i]->getPositionX() && snake->getPositionY() == bodySegments[i]->getPositionY())
		{
			snake->doDeath();
			break;  
		}
	}
}

void GameScene::spawnBodySegment()
{
	Body* anotherSegment = new Body();
	this->addGameObject(anotherSegment);
	bodySegments.push_back(anotherSegment);

	if (bodySegments.size() > 1)
	{
		for (int i = bodySegments.size() - 1; i > 0; i--)
		{
			int lastIndex = i - 1;
			anotherSegment->setPosition(bodySegments[lastIndex]->getPositionX(), bodySegments[lastIndex]->getPositionY());
		}
	}
	else
	{
		anotherSegment->setPosition(snake->getPreviousPositionX(), snake->getPreviousPositionY());
	}
}
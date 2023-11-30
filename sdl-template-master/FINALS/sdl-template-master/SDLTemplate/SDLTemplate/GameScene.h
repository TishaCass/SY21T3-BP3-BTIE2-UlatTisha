#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "draw.h"
#include "Snake.h"
#include "Fruit.h"
#include "Body.h"
#include <deque>


class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

	void spawnFruit();

	void checkCollision();

private:
	SDL_Texture* background;

	int screenWidth;
	int screenHeight;
	int fruitSpawnInterval;

	Snake* player;
	Fruit* newFruit;

	std::vector<Fruit*> spawnedFruit;
};
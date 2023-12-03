#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "draw.h"
#include "Snake.h"
#include "Fruit.h"
#include "Body.h"
#include "text.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();

	void spawnFruit();
	void despawnFruit();
	void checkCollisionFruit();
	void checkCollisionBody();
	void spawnBodySegment();

private:
	SDL_Texture* background;

	int screenWidth;
	int screenHeight;
	int fruitSpawnInterval;
	int bodyInterval;

	Snake* snake;
	Fruit* newFruit;

	std::vector<Fruit*> spawnedFruit;
	std::vector<Body*> bodySegments;
};
#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "draw.h"
#include "Explosion.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Enemy* enemy;

	SDL_Texture* background;

	//Enemy Spawning
	float spawnTimer;
	float currentSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;
	std::vector<Explosion*> explosions;

	void doSpawnLogin();
	void doCollisionLogic();

	void explosion(Enemy* enemy);

	void spawn();
	void despawnEnemy(Enemy* enemy);

	int points; 
};


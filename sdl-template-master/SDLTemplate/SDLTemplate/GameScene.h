#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>
#include "text.h"
#include "draw.h"
#include "Explosion.h"
#include "PowerUp.h"

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
	Mix_Chunk* sound;

	//Enemy Spawning
	float spawnTimer;
	float currentSpawnTimer;
	float PowerUpSpawn;
	float currentPowerUpSpawn;
	

	std::vector<Enemy*> spawnedEnemies;
	std::vector<Explosion*> explosions;
	std::vector<PowerUp*> powerUps;


	void doSpawnLogin();
	void doCollisionLogic();

	void explosion(Enemy* enemy);

	void spawn();
	void despawnEnemy(Enemy* enemy);

	void spawnPowerUp();

	int points; 
};


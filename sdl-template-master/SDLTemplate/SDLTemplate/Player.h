#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player : public GameObject
{
public:
	~Player();
	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
	bool getIsAlive();
	void doDeath();

	void doPowerUp();

private:
	SDL_Texture* playerShip;
	Mix_Chunk* sound;
	int x;
	int y;
	int width;
	int height;
	int speed;
	int speedBoost;
	float reloadTime;
	float currentReloadTime;

	float reloadTimeWing;
	float currentReloadTimeWing;
	bool isPowerUpActive = false;
	int powerUpDuration = 500; 
	int currentPowerUpDuration = 0;

	std::vector<Bullet*> bullets;
	bool isAlive;
};


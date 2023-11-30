#include "Player.h"
#include "Scene.h"
Player::~Player()
{
	// Memory manage bullets, delete all bullets when player dies
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}
void Player::start()
{
	//load Texture
	playerShip = loadTexture("gfx/playerRotate.png");

	//Initialize Variables
	x = 100;
	y = SCREEN_HEIGHT - 100;
	width = 4;
	height = 4;
	speed = 3;
	speedBoost = 6;
	reloadTime = 14;
	currentReloadTime = 0;

	reloadTimeWing = 18;
	currentReloadTimeWing = 0;
	isPowerUpActive = false;

	isAlive = true;

	//Query the texture for width and height
	SDL_QueryTexture(playerShip, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			// Cache the variable so we can delete it later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}

	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = speedBoost;
	}
	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 2;
	}

	// decerement the player's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	// decrement the player's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);

		if (isPowerUpActive)
		{
			Bullet* bulletCenter = new Bullet(x - 2 + width / 2, y - 30, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bulletCenter);
			getScene()->addGameObject(bulletCenter);

			Bullet* bulletLeft = new Bullet(this->getPositionX(), this->getPositionY(), 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bulletLeft);
			getScene()->addGameObject(bulletLeft);
			bulletLeft->start();

			Bullet* bulletRight = new Bullet(this->getPositionX() + 35, this->getPositionY(), 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bulletRight);
			getScene()->addGameObject(bulletRight);

			currentReloadTimeWing = reloadTimeWing;
		}
		else
		{
			// If power-up is not active, shoot a single bullet
			Bullet* bullet = new Bullet(x - 2 + width / 2, y - 30, 0, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
		}

		currentReloadTime = reloadTime;
	}

	if (isPowerUpActive && currentPowerUpDuration > 0)
	{
		currentPowerUpDuration--;

		if (currentPowerUpDuration == 0)
		{
			isPowerUpActive = false;
		}
	}
}

void Player::draw()
{
	//draw texture
	if (!isAlive) return;
	blit(playerShip, x, y);
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
}

void Player::doDeath()
{
	isAlive = false;
}

void Player::doPowerUp()
{
	isPowerUpActive = true;
	currentPowerUpDuration = powerUpDuration;
}


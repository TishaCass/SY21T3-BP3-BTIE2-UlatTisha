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
	texture = loadTexture("gfx/player.png");

	//Initialize Variables
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	speedBoost = 5;
	reloadTime = 8;
	currentReloadTime = 0;
	reloadTimeWing = 10;
	currentReloadTimeWing = 0;

	//Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
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

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// After firing reset reload time
		currentReloadTime = reloadTime;
	}

	if (currentReloadTimeWing > 0)
		currentReloadTimeWing--;

	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTimeWing == 0)
	{
		SoundManager::playSound(sound);
		Bullet* bulletUp = new Bullet(x + 5, y, 1, 0, 10);
		bullets.push_back(bulletUp);
		getScene()->addGameObject(bulletUp);
		bulletUp->start();

		Bullet* bulletDown = new Bullet(x + 5, y + 35, 1, 0, 10);
		bullets.push_back(bulletDown);
		getScene()->addGameObject(bulletDown);
		bulletDown->start();

		// After firing reset reload time
		currentReloadTimeWing = reloadTimeWing;
	}

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
}

void Player::draw()
{
	//draww texture
	blit(texture, x, y);
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

#include "Enemy.h"
#include "Scene.h"
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	//load Texture
	texture = loadTexture("gfx/enemy.png");

	//Initialize Variables
	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadTime = 60;
	currentReloadTime = 0;
	directionChangeTime = (rand() % 300) + 100; // Direction change time 3-8 seconds
	currentDirectionChangeTime = 0;

	//Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Enemy::update()
{
	//move
	x += directionX * speed;
	y += directionY * speed;

	//Basic AI, switch direction every X seconds
	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		//Flip diretions
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	//Decrement the enemy's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	//Only fire when reload time is ready
	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// After firing reset reload time
		currentReloadTime = reloadTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			// Cache the variable so we can delete it later
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}
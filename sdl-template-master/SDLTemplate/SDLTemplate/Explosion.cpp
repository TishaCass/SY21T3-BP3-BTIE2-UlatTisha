#include "Explosion.h"


Explosion::Explosion(float positionX, float positionY, float width, float height)
{
	this->x = positionX;
	this->y = positionY;

	this->width = width;
	this->height = height;

}

void Explosion::start()
{
	time = 40;

	explode = loadTexture("gfx/explosion.png");

	SDL_QueryTexture(explode, NULL, NULL, &width, &height);
}

void Explosion::update()
{
	if (time > 0)
	{
		time--;
	}
}

void Explosion::draw()
{
	blit(explode, x, y);
}

int Explosion::getPositionX()
{
	return x;
}

int Explosion::getPositionY()
{
	return y;
}

int Explosion::getWidth()
{
	return width;
}

int Explosion::getHeight()
{
	return height;
}

int Explosion::getTime()
{
	return time;
}

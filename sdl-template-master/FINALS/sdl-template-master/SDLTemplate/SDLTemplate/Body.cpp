#include "Body.h"

Body::Body()
{
}

void Body::start()
{
	width = 30;
	height = 30;

	bodySegment = loadTexture("gfx/snakeSegment.png");

	SDL_QueryTexture(bodySegment, NULL, NULL, &width, &height);
}

void Body::update()
{
}

void Body::draw()
{
	blit(bodySegment, x, y);
}

int Body::getPositionX()
{
	return x;
}

int Body::getPositionY()
{
	return y;
}

int Body::getWidth()
{
	return width;
}

int Body::getHeight()
{
	return height;
}

void Body::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
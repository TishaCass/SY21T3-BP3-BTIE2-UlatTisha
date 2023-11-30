#include "Fruit.h"

Fruit::Fruit()
{
    // Load the texture and initialize other members in the constructor
    fruit = loadTexture("gfx/fruit.png");

    width = 30;
    height = 30;

	// Initialize x and y within the desired range
	x = (rand() % (600 / fruitInterval) * fruitInterval) + 30;
	y = (rand() % (600 / fruitInterval) * fruitInterval) + 30;
}

Fruit::~Fruit()
{
	delete fruit;
}

void Fruit::start()
{
}

void Fruit::update()
{
}

void Fruit::draw()
{
	blit(fruit, x, y);
}

int Fruit::getPositionX()
{
	return x;
}

int Fruit::getPositionY()
{
	return y;
}

int Fruit::getWidth()
{
	return width;
}

int Fruit::getHeight()
{
	return height;
}
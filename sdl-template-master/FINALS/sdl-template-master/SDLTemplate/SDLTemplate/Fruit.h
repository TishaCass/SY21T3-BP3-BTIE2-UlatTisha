#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Scene.h"

class Fruit : public GameObject
{
public:
	Fruit();
	~Fruit();

	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

private:
	SDL_Texture* fruit;

	int x;
	int y;
	int width;
	int height;
	int fruitInterval = 30;
};
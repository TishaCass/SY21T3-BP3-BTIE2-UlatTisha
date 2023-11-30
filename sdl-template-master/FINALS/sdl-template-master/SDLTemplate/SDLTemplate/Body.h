#pragma once
#include "Snake.h"
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Scene.h"

class Body : public GameObject
{
public:
	Body();

	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

	void setPosition(int x, int y);

private:
	SDL_Texture* bodySegment;

	int x;
	int y;
	int width;
	int height;
};
#pragma once
#include "GameObject.h"
#include "draw.h"
#include "text.h"

class Explosion : public GameObject
{
public:

    Explosion(float positionX, float positionY, float width, float height);

    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    int getTime();

private:
    SDL_Texture* explode;

    int x;
    int y;
    int width;
    int height;
    int time;
};


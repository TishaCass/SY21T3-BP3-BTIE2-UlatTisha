#include "PowerUp.h"


PowerUp::PowerUp()
{
    speed = 3;
}

PowerUp::~PowerUp()
{
}

void PowerUp::start()
{
    powerUp = loadTexture("gfx/powerUp.png");
    x = rand() % (SCREEN_WIDTH / 2);
    y = 0;
    height = 5;
    width = 5;
}

void PowerUp::update(std::vector<PowerUp*>& powerUps, int i)
{
    y += speed;

    if (y > SCREEN_HEIGHT)
    {
        powerUps.erase(powerUps.begin() + i);
        delete this; 
    }
}


void PowerUp::draw()
{
    blit(powerUp, x, y);
}

int PowerUp::getPositionX()
{
    return x;
}

int PowerUp::getPositionY()
{
    return y;
}
int PowerUp::getWidth()
{
    return width;
}

int PowerUp::getHeight()
{
    return height;
}
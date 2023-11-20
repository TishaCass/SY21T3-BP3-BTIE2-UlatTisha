#pragma once
#include "GameObject.h"
#include "defs.h"
#include "draw.h"
#include "Scene.h"
#include <SDL.h>

class PowerUp : public GameObject
{
public:
    PowerUp();
    ~PowerUp();

    void start();
    void update(std::vector<PowerUp*>& powerUps, int i);
    void draw();
    int getWidth();
    int getHeight();
    int getPositionX();
    int getPositionY();

private:
   
    SDL_Texture* powerUp;
    int x;
    int y;
    int width;
    int height;
    int speed;
    bool isCollected;

};

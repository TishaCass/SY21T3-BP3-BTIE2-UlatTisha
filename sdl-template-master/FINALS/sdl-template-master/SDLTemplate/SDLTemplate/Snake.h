#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Snake : public GameObject
{
public:
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getPreviousPositionX();
    int getPreviousPositionY();
    int getWidth();
    int getHeight();

    bool getIsAlive();
    void doDeath();

private:
    SDL_Texture* snakeHead;

    int x;
    int y;
    int prevX;
    int prevY;
    int width;
    int height;

    int speed;
    int counter;
    int currentCounter;

    int velocityX;
    int velocityY;

    bool isAlive;
};                                     
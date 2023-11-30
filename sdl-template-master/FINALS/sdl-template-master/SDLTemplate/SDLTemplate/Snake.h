#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include <vector>
#include "Body.h"

class Snake : public GameObject
{
public:
    void start();
    void update();
    void draw();

    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    bool getIsAlive();
    void doDeath();
    void drawBody();

private:
    SDL_Texture* snakeHead;

    int x;
    int y;
    int width;
    int height;
    int speed;
    int velocityX;
    int velocityY;

    bool isAlive;

    int counter;
    int currentCounter;
    int numBodySegment;

    std::vector <Body*> spawnedBody;
};
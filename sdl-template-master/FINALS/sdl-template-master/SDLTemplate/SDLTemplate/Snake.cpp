#include "Snake.h"

void Snake::start()
{
    // Load texture
    snakeHead = loadTexture("gfx/snakeSegment.png");

    isAlive = true;
    x = 90;
    y = 330;
    prevX = x;
    prevY = y;
    width = 30;
    height = 30;
    speed = 30;
    counter = 15;
    currentCounter = 0;

    SDL_QueryTexture(snakeHead, NULL, NULL, &width, &height);
}

void Snake::update()
{
    if (!isAlive) return;

    if (currentCounter > 0)
        currentCounter--;
    else
    {
        prevX = x;
        prevY = y;

        // Adjust the velocity based on the first pressed key
        if (app.keyboard[SDL_SCANCODE_W] && !app.keyboard[SDL_SCANCODE_S])
        {
            velocityX = 0;
            velocityY = -speed; // Move up
        }
        else if (app.keyboard[SDL_SCANCODE_S] && !app.keyboard[SDL_SCANCODE_W])
        {
            velocityX = 0;
            velocityY = speed; // Move down
        }
        else if (app.keyboard[SDL_SCANCODE_A] &&!app.keyboard[SDL_SCANCODE_D])
        {
            velocityY = 0;
            velocityX = -speed; // Move left
        }
        else if (app.keyboard[SDL_SCANCODE_D] && !app.keyboard[SDL_SCANCODE_A])
        {
            velocityY = 0;
            velocityX = speed; // Move right
        }

        x += velocityX;
        y += velocityY;

        // Update the counter to control the frame rate
        currentCounter = counter;
    }
}

void Snake::draw()
{
    blit(snakeHead, x, y);
}

int Snake::getPositionX()
{
    return x;
}

int Snake::getPositionY()
{
    return y;
}

int Snake::getPreviousPositionX()
{
    return prevX;
}

int Snake::getPreviousPositionY()
{
    return prevY;
}

int Snake::getWidth()
{
    return width;
}

int Snake::getHeight()
{
    return height;
}

bool Snake::getIsAlive()
{
    return isAlive;
}

void Snake::doDeath()
{
    isAlive = false;
}
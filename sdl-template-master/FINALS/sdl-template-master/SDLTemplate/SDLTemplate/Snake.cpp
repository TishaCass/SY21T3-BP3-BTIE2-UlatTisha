#include "Snake.h"

void Snake::start()
{
    // Load texture
    snakeHead = loadTexture("gfx/snakeSegment.png");

    isAlive = true;
    x = 90;
    y = 330;
    width = 30;
    height = 30;
    speed = 30;
    counter = 9;
    currentCounter = 0;

    SDL_QueryTexture(snakeHead, NULL, NULL, &width, &height);

    // Initialize the spawnedBody vector as an empty vector
    spawnedBody.clear();

    // Create the initial body segment
    Body* initialSegment = new Body();
    initialSegment->start();
    initialSegment->setPosition(x - width, y);
    spawnedBody.push_back(initialSegment);  // Use push_back to add elements
    numBodySegment = 1;
}

void Snake::update()
{
    if (!isAlive) return;

    if (currentCounter > 0)
        currentCounter--;
    else
    {
        // Adjust the velocity based on the first pressed key
        if (app.keyboard[SDL_SCANCODE_W])
        {
            velocityX = 0;
            velocityY = -speed; // Move up
        }
        else if (app.keyboard[SDL_SCANCODE_S])
        {
            velocityX = 0;
            velocityY = speed; // Move down
        }
        else if (app.keyboard[SDL_SCANCODE_A])
        {
            velocityY = 0;
            velocityX = -speed; // Move left
        }
        else if (app.keyboard[SDL_SCANCODE_D])
        {
            velocityY = 0;
            velocityX = speed; // Move right
        }

        x += velocityX;
        y += velocityY;

        // Update the counter to control the frame rate
        currentCounter = counter;
    }

    // Move the body segments
    for (int i = numBodySegment - 1; i > 0; --i) {
        int prevX = spawnedBody[i - 1]->getPositionX();
        int prevY = spawnedBody[i - 1]->getPositionY();
        spawnedBody[i]->setPosition(prevX, prevY);
    }

    // Move the first body segment to the snake's head position
    if (numBodySegment > 0) {
        int headX = getPositionX();
        int headY = getPositionY();
        spawnedBody[0]->setPosition(headX, headY);
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

void Snake::drawBody() {
    for (int i = 0; i < numBodySegment; ++i) 
    {
        spawnedBody[i]->draw();
    }
}
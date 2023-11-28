#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::start()
{
    //load Texture
    texture = loadTexture("gfx/9.png");

    //Initialize Variables
    directionX = -1;
    directionY = 1;
    width = 4;
    height = 4;
    speed = 2;
    reloadTime = 60;
    currentReloadTime = 0;
    directionChangeTime = (rand() % 100) + 100; // Direction change time 3-8 seconds
    currentDirectionChangeTime = 0;
    health = 50; //initialize boss hp

    //Query the texture for width and height
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
    sound->volume = 64;
}

void Boss::update()
{
    // Move horizontally
    x += directionX * speed;
    y += 0.5;
    // Basic AI, switch direction every X seconds
    if (currentDirectionChangeTime > 0)
        currentDirectionChangeTime--;

    if (currentDirectionChangeTime == 0)
    {
        // Flip directions in the horizontal axis
        directionX = -directionX;
        currentDirectionChangeTime = directionChangeTime;
    }

    // Update the firing timer
    if (currentReloadTime > 0)
        currentReloadTime--;

    // Only fire when reload time is ready
    if (currentReloadTime == 0)
    {
        // Fire multiple bullets in a "rain" pattern
        const int numBullets = 5;  // Adjust the number of bullets as needed

        for (int i = 0; i < numBullets; ++i)
        {
            int bulletSpacing = 20;

            // Play sound and fire bullet
            SoundManager::playSound(sound);
           
            Bullet* bulletLeftBack = new Bullet(x + width / 2 - bulletSpacing,y + height / 2 - 20, 0, 1, 10, Side::ENEMY_SIDE);
            bullets.push_back(bulletLeftBack);
            getScene()->addGameObject(bulletLeftBack);
            bulletLeftBack->start();

            Bullet* bulletRightBack = new Bullet(x + width / 2 + bulletSpacing, y + height / 2 - 20, 0, 1, 10, Side::ENEMY_SIDE);
            bullets.push_back(bulletRightBack);
            getScene()->addGameObject(bulletRightBack);

            Bullet* bulletLeft = new Bullet(x + width / 2 - bulletSpacing - 60, y + height - 30, 0, 1, 10, Side::ENEMY_SIDE);
            bullets.push_back(bulletLeft);
            getScene()->addGameObject(bulletLeft);
            bulletLeft->start();

            Bullet* bulletRight = new Bullet(x + width / 2 + bulletSpacing + 60, y + height - 30, 0, 1, 10, Side::ENEMY_SIDE);
            bullets.push_back(bulletRight);
            getScene()->addGameObject(bulletRight);

        }

        // After firing, reset the reload time
        currentReloadTime = reloadTime;
    }

    // Check and handle bullet removal
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i]->getPositionX() < 0)
        {
            // Cache the variable so we can delete it later
            Bullet* bulletToErase = bullets[i];
            bullets.erase(bullets.begin() + i);
            delete bulletToErase;

            break;
        }
    }
}

void Boss::draw()
{
    blit(texture, x, y);
}

void Boss::setPlayerTarget(Player* player)
{
    playerTarget = player;
}

void Boss::setPosition(int xPos, int yPos)
{
    this->x = xPos;
    this->y = yPos;
}

void Boss::setHealth(int newHealth)
{
    health = newHealth;
}

int Boss::getPositionX()
{
    return x;
}

int Boss::getPositionY()
{
    return y;
}

int Boss::getWidth()
{
    return width;
}

int Boss::getHeight()
{
    return height;
}

int Boss::getHealth()
{
    return health;
}

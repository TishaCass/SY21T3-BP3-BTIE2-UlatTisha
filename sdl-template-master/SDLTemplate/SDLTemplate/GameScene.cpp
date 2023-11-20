#include "GameScene.h"

GameScene::GameScene()
{
    // Register and add game objects on constructor

    player = new Player();
    this->addGameObject(player);

    points = 0;
}

GameScene::~GameScene()
{
    delete player;
}

void GameScene::start()
{
    Scene::start();

    background = loadTexture("gfx/Background_.png");

    sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");

    // Initialize any scene logic here

    initFonts();

    currentSpawnTimer = 300;
    spawnTimer = 300; // Spawn time of 5 secs

    currentPowerUpSpawn = 1200;
    PowerUpSpawn = 1200; // Spawn powerUps every 20 secs

    spawn();

    spawnPowerUp();
}

void GameScene::draw()
{
    //draw texture

    int Height = 1000;
    int Width = 700;

    blit(background, 0, 0);

    blitScale(background, 0, 0, &Width, &Height, 3);

    Scene::draw();

    drawText(100, 20, 225, 225, 225, TEXT_CENTER, "SCORE: %03d", points);

    if (player->getIsAlive() == false)
    {
        drawText(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 6, 225, 225, 225, TEXT_CENTER, "GAME OVER!");
    }
}

void GameScene::update()
{
    Scene::update();

    doSpawnLogin();
    doCollisionLogic();

    for (int i = 0; i < objects.size(); i++)
    {
        Explosion* Explosions = dynamic_cast<Explosion*>(objects[i]);

        if (Explosions != NULL)
        {
            if (Explosions->getTime() <= 0)
            {
                Explosion* explosionsDone = Explosions;
                explosions.erase(explosions.begin());
                delete explosionsDone;
            }
        }
    }

    for (int i = 0; i < powerUps.size(); i++)
    {
        powerUps[i]->update(powerUps, i);
    }
}

void GameScene::doSpawnLogin()
{
    if (currentSpawnTimer > 0)
        currentSpawnTimer--;

    if (currentSpawnTimer <= 0)
    {
        currentSpawnTimer = spawnTimer;
        spawn();
    }

    if (currentPowerUpSpawn > 0)
        currentPowerUpSpawn--;

    if (currentPowerUpSpawn <= 0)
    {
        currentPowerUpSpawn = PowerUpSpawn;
        spawnPowerUp();
    }
}

void GameScene::doCollisionLogic()
{
    // Checking for collisions
    for (int i = 0; i < objects.size(); i++)
    {
        Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

        if (bullet != NULL)
        {
            if (bullet->getSide() == Side::ENEMY_SIDE)
            {
                int collision = checkCollision(
                    player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                    bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
                );

                if (collision == 1)
                {
                    player->doDeath();
                    break;
                }
            }
            else if (bullet->getSide() == Side::PLAYER_SIDE)
            {
                for (int j = 0; j < spawnedEnemies.size(); j++)
                {
                    Enemy* currentEnemy = spawnedEnemies[j];

                    int collision = checkCollision(
                        currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
                        bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
                    );

                    if (collision == 1)
                    {
                        explosion(currentEnemy);
                        despawnEnemy(currentEnemy);
                        points++;

                        break;
                    }
                }
            }
        }

        PowerUp* powerUp = dynamic_cast<PowerUp*>(objects[i]);
        if (powerUp != NULL)
        {
            int collisionPowerUp = checkCollision(
                player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
                powerUp->getPositionX(), powerUp->getPositionY(), powerUp->getWidth(), powerUp->getHeight()
            );

            if (collisionPowerUp == 1)
            {
                player->doPowerUp();

                PowerUp* powerUpDone = powerUp;
                powerUps.erase(powerUps.begin());
                delete powerUp;
            }
        }
    }
    for (int i = 0; i < spawnedEnemies.size(); i++)
    {
        if (spawnedEnemies[i]->getPositionY() > SCREEN_HEIGHT)
        {
            Enemy* enemyToErase = spawnedEnemies[i];
            spawnedEnemies.erase(spawnedEnemies.begin() + i);
            delete enemyToErase;

            break;
        }
    }
}

void GameScene::explosion(Enemy* enemy)
{
    Explosion* explosion = new Explosion(enemy->getPositionX(), enemy->getPositionY(), enemy->getWidth(), enemy->getHeight());

    this->addGameObject(explosion);
    explosions.push_back(explosion);
}

void GameScene::spawn()
{
    Enemy* enemy = new Enemy();
    this->addGameObject(enemy);
    enemy->setPlayerTarget(player);

    enemy->setPosition(0 + (rand() % 500), -50);
    spawnedEnemies.push_back(enemy);
}

void GameScene::despawnEnemy(Enemy* enemy)
{
    int index = -1;
    for (int i = 0; i < spawnedEnemies.size(); i++)
    {
        if (enemy == spawnedEnemies[i])
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        spawnedEnemies.erase(spawnedEnemies.begin() + index);
        delete enemy;
    }
}

void GameScene::spawnPowerUp()
{
    PowerUp* powerUp = new PowerUp();
    this->addGameObject(powerUp);
    powerUps.push_back(powerUp);
}
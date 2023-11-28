#include "GameScene.h"
#include "Boss.h"

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

    initFonts();

    currentSpawnTimer = 300;
    spawnTimer = 250;

    currentPowerUpSpawn = 1200;
    PowerUpSpawn = 1000;

    spawn();

    spawnPowerUp();

    bossSpawned = false;
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

    if (bossSpawned == true)
    {
        drawText(600, 20, 225, 225, 225, TEXT_CENTER, "BOSS HP: %03d", HP);
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

    spawnBoss();
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
    std::vector<Bullet*> bulletsMarkedForDeletion;

    // Checking for collisions with enemies
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
                        bulletsMarkedForDeletion.push_back(bullet);
                        break;
                    }
                }

                for (int k = 0; k < spawnedBoss.size(); k++)
                {
                    Boss* currentBoss = spawnedBoss[k];

                    if (currentBoss != NULL && bullet->getSide() == Side::PLAYER_SIDE)
                    {
                        int collision = checkCollision(
                            currentBoss->getPositionX(), currentBoss->getPositionY(), currentBoss->getWidth(), currentBoss->getHeight(),
                            bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
                        );

                        if (collision == 1)
                        {
                            std::cout << "enemy hit. HP before" << currentBoss->getHealth() << std::endl;
                            currentBoss->setHealth(currentBoss->getHealth() - 1);
                            std::cout << " After" << currentBoss->getHealth() << std::endl;

                            if (currentBoss->getHealth() <= 0)
                            {
                                // Boss is defeated, remove and delete it
                                despawnBoss(currentBoss);
                            }

                            bulletsMarkedForDeletion.push_back(bullet);
                            break;
                        }
                    }
                    HP = currentBoss->getHealth();
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

    // Remove bullets after the loop
    for (int i = 0; i < bulletsMarkedForDeletion.size(); i++)
    {
        Bullet* bulletsToRemove = bulletsMarkedForDeletion[i];
        bulletsMarkedForDeletion.erase(bulletsMarkedForDeletion.begin() + i);
        delete bulletsToRemove;
        break;
    }


    // Check if enemies have moved out of the screen and remove them
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
    if (bossSpawned == false)
    {
        Enemy* enemy = new Enemy();
        this->addGameObject(enemy);
        enemy->setPlayerTarget(player);

        enemy->setPosition(0 + (rand() % 500), -50);
        spawnedEnemies.push_back(enemy);
    }
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

void GameScene::spawnBoss()
{
    // Check if points are greater than or equal to a threshold and there is no existing boss
    if (points == 15 && spawnedBoss.size() == 0 && bossSpawned == false)
    {
        Boss* boss = new Boss();
        this->addGameObject(boss);
        boss->setPlayerTarget(player);

        boss->setPosition(-20 + (rand() % 300), -50);
        spawnedBoss.push_back(boss);

        bossSpawned = true;
    }
}

void GameScene::despawnBoss(Boss* boss)
{
    int index = -1;
    for (int i = 0; i < spawnedBoss.size(); i++)
    {
        if (boss == spawnedBoss[i])
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        spawnedBoss.erase(spawnedBoss.begin() + index);
        delete boss;

        points += 10;
    }

    bossSpawned = false;
}
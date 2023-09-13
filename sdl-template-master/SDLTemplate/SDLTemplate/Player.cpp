#include "Player.h"

void Player::start()
{
	//load Texture
	texture = loadTexture("gfx/player.png");

	//Initialize Variables
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	speedBoost = 5;

	//Query the texture for width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = speedBoost;
	}
	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 2;
	}
}

void Player::draw()
{
	//draww texture
	blit(texture, x, y);
}

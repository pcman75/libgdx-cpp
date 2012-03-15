#include "stdafx.h"
#include "Hat.h"
#include "Level.h"
#include "Player.h"
#include "TextureRegion.h"
#include "SoundMeta.h"
#include "Bullet.h"
#include "Screen.h"

Hat::Hat (double x, double y) 
{
  time = 0;
	noTakeTime = 30;
	this->x = x;
	this->y = y;
	this->xPos = -1;
	this->yPos = -1;
  xxa = 0;
	w = 6;
	h = 3;
	bounce = 0;
	ya = -1;
	time = MathUtils::PI * 0.5;
}

Hat::Hat (double x, double y, int xPos, int yPos) 
{
  time = 0;
	noTakeTime = 30;
	this->x = x;
	this->y = y;
	this->xPos = xPos;
	this->yPos = yPos;
	w = 6;
	h = 3;
	bounce = 0;
	ya = -1;
	time = MathUtils::PI * 0.5;
}

void Hat::tick () 
{
	tryMove(xa, ya);
	if (onGround) 
  {
		time = 0;
	} 
  else 
  {
		time++;
	}

	xa = xxa + MathUtils::sin(time * 0.05) * 0.2;
	xxa *= 0.95;
	ya *= 0.95;
	ya += Level::GRAVITY * 0.1;

	if (noTakeTime > 0)
		noTakeTime--;
	else 
  {
		std::vector<Entity*> entities = level->getEntities((int)x, (int)y, w, h);
		for (int i = 0; i < entities.size(); i++) 
    {
			Entity* e = entities[i];
      Player* player = dynamic_cast<Player*>(e);

			if( NULL != player) 
      {
				player->hatCount++;

				if (xPos >= 0 && yPos >= 0) 
        {
					Art::level->setColor(0, 0, 0, 0);
					Art::level->drawPixel(xPos, yPos);
				}
				//SoundMeta::gethat->play();
				remove();
			}
		}
	}
}

void Hat::render (Screen* g, Camera* camera) 
{
	int dir = 1;
	int xp = (int)x - (16 - w) / 2;
	int yp = (int)y - 2;
	TextureRegion*** sheet = dir == 1 ? Art::player1 : Art::player2;

	int xFrame = (int)(xa * 10);
	if (xFrame < -1) xFrame = -1;
	if (xFrame > +1) xFrame = +1;
	g->draw(sheet[1 + xFrame][1], xp, yp);
}

bool Hat::shot (Bullet* bullet) 
{
	//SoundMeta::hit->play();
	xa += bullet->xa * 0.5;
	ya += bullet->ya * 0.5;

	return true;
}



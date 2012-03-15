#include "stdafx.h"
#include "Sign.h"
#include "Player.h"
#include "Art.h"
#include "Level.h"
#include "Screen.h"

Sign::Sign (int x, int y, int id) 
{
  autoRead = false;
	this->x = x;
	this->y = y;
	this->w = 6;
	this->h = 6;
	xa = ya = 0;
	this->id = id;
	autoRead = ( id == 1);
	if (id == 6) autoRead = true;
	if (id == 15) autoRead = true;
}

void Sign::tick () 
{
	if (id == 6 && level->player->gunLevel >= 1) remove();
	if (id == 15 && level->player->gunLevel >= 2) remove();
	std::vector<Entity*> entities = level->getEntities((int)x, (int)y, 6, 6);
	for (int i = 0; i < entities.size(); i++) 
  {
		Entity* e = entities[ i];
    Player* player = dynamic_cast<Player*>( e);
		if(player) 
    {
			player->readSign(this);
		}
	}
}

void Sign::render (Screen* g, Camera* camera) 
{
	if (id == 6 && level->player->gunLevel >= 1) return;
	if (id == 15 && level->player->gunLevel >= 2) return;
	if (id == 6) 
  {
		g->draw(Art::walls[5][0], (int)x, (int)y);
	} 
  else if (id == 15) 
  {
		g->draw(Art::walls[6][0], (int)x, (int)y);
	} 
  else 
  {
		g->draw(Art::walls[4][0], (int)x, (int)y);
	}
}
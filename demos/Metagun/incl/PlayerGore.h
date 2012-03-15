#pragma once
#include "Entity.h"

class PlayerGore : public Entity 
{
private:
  int life;

public:
  PlayerGore (double x, double y) ;

	void tick () ;

	void hitWall (double xa, double ya) ;

	void render (Screen* g, Camera* camera) ;

	void hitSpikes () ;

};

#pragma once
#include "Entity.h"

class HeadGore : public Entity 
{
private:
  int life;

public:
  HeadGore (double x, double y) ;

	void tick () ;

  void hitWall (double xa, double ya) ;

	void render (Screen* g, Camera* camera) ;

	void hitSpikes () ;

};

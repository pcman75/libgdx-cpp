#pragma once
#include "Entity.h"

class Spark : public Entity 
{
private:
  int life;

public:
  Spark (double x, double y, double xa, double ya) ;

	void tick () ;

	void hitWall (double xa, double ya) ;

	void render (Screen* g, Camera* camera) ;
};

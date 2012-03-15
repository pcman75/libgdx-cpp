#pragma once
#include "Entity.h"

class Gore : public Entity 
{
private:
  int life;

public:
  Gore (double x, double y, double xa, double ya) ;

	void tick () ;

	void hitWall (double xa, double ya) ;

	void render (Screen* g, Camera* camera) ;

};

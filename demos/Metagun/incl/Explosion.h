#pragma once
#include "Entity.h"

class Explosion : public Entity 
{
private:
  int life, delay, color;
	int duration;

public:
  int power;

public:
  Explosion (int power, int delay, double x, double y, double xa, double ya) ;

	void tick () ;
  
	void hitWall (double xa, double ya) ;
  
  void render (Screen* g, Camera* camera) ;
};

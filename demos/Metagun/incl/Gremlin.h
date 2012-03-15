#pragma once
#include "Entity.h"

class Gremlin : public Entity 
{
private:
  static int MAX_TEMPERATURE;
	int temperature;
	int power;

public:
  int jumpDelay;

public:
  Gremlin (int power, int x, int y) ;

	void tick () ;

	void render (Screen* g, Camera* camera) ;

	void hitSpikes () ;

	void die () ;

	bool shot (Bullet* bullet) ;

	void explode (Explosion* explosion) ;

};

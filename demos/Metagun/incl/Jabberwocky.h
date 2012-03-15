#pragma once
#include "Entity.h"


class Jabberwocky : public Entity 
{
private:
  static int MAX_TEMPERATURE;
	int temperature;
public: 
  int slamTime;

public:
  Jabberwocky (int x, int y) ;

	void tick () ;

	void render (Screen* g, Camera* camera) ;

  void Jabberwocky::hitSpikes () ;

  void Jabberwocky::die () ;

	bool shot (Bullet* bullet) ;

	void explode (Explosion* explosion) ;

};

#pragma once
#include "Entity.h"


class Gunner : public Entity 
{
private:
  int sliding;

public:
  static int CHARGE_DURATION;
	int chargeTime;
	

public:
  Gunner (double x, double y, double xa, double ya) ;

	void tick () ;

	void hitWall (double xa, double ya) ;

	virtual void render (Screen* g, Camera* camera) ;

	bool shot (Bullet* bullet) ;

	void hitSpikes () ;

	void die () ;

	void shove (Gunner* enemy) ;

	void explode (Explosion* explosion) ;

	void collideMonster (Entity* e) ;

};

#pragma once 
#include "BossPart.h"

class BossNeck : public BossPart 
{
public:
  int slamTime;
	BossPart* child;
	double baseRot;
	double rot, rota;
	int time;

public:
	BossNeck (int x, int y, BossPart* child) ;

	void tick () ;

	void setRot (double rot) ;

	void render( Screen* screen, Camera* camera) ;

  void hitSpikes () ;
	
  void die () ;
  
	bool shot (Bullet* bullet) ;
  
  void explode (Explosion* explosion) ;
  
};

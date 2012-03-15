#pragma once
#include "BossPart.h"
class Screen;
class Camera;
class Bullet;
class Explosion;


class Boss : public BossPart 
{
private:
  static int MAX_TEMPERATURE;
	int temperature;
	double xo, yo;

public:
  int slamTime;
  int time;

public:
	Boss (int x, int y) ;
  
	void tick () ;
  
	void render (Screen* screen, Camera* camera) ;
  
	void hitSpikes () ;
  
  void die () ;
  
	bool shot (Bullet* bullet) ;
  
	void explode (Explosion* explosion) ;
  

};

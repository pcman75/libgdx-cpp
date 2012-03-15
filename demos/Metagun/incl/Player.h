#pragma once
#include "Entity.h"
#include "InputMeta.h"
class Sign;

class Player : public Entity 
{
private:
  int dir;
	int yAim;
	int frame;
	int noHurtTime;
  int shootTime;
public:
  int gunLevel;
	bool breadSign;
  int hatCount;
	int damage;

public:
  Player (int x, int y) ;

	void tick () ;

	void render (Screen* g, Camera* camera) ;

	void tick (InputMeta* input) ;

	void hitSpikes () ;

	void die () ;

	bool shot (Bullet* bullet) ;

	void readSign (Sign* sign) ;
  
	void outOfBounds () ;
  
	void explode (Explosion* explosion) ;
  
	void collideMonster (Entity* e) ;
  

};

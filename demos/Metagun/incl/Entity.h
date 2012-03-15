#pragma once
class Level;
class Screen;
class Camera;
class Bullet;
class Gunner;
class Explosion;


class Entity 
{
protected:
  bool onGround;
	//static Random random;

public:
  double xa, ya;
	double x, y;
	double bounce;
	int w, h;

	Level* level;
	bool removed;
	int xSlot, ySlot;

	bool interactsWithWorld;

public:
  Entity();

  virtual void init( Level* level) ;

	virtual void tryMove (double xa, double ya) ;
  
	virtual void hitWall (double xa, double ya) ;
  
	virtual void remove () ;
  
	virtual void tick () ;
  
	virtual void render(Screen* screen, Camera* camera) = 0;

	virtual bool shot (Bullet* bullet) ;
  
	virtual void hitSpikes () ;
  
	virtual void shove( Gunner* enemy) ;
  
	virtual void outOfBounds () ;
  
	virtual void explode( Explosion* explosion) ;
  
	virtual void collideMonster( Entity* e) ;
  
};

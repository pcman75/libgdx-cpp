#pragma once
#include "Matrix4.h"
class Entity;
class Player;
class Screen;
class GameScreen;
class Sign;
class Camera;

class Level 
{
public:
  static double FRICTION;
	static double GRAVITY;

	std::list<Entity*> entities;
	unsigned char* walls;
	std::vector<std::list<Entity*>> entityMap;
	int width, height;
	Player* player;
	int xSpawn, ySpawn;
	//Random random = new Random(1000);
	GameScreen* screen;
	int respawnTime;
	// private int xo, yo;
	int ntick;
  std::vector<Entity*> hits;
  Matrix4 matrix;

public:
	Level (GameScreen* screen, int w, int h, int xo, int yo, int xSpawn, int ySpawn) ;

	void add (Entity* e) ;

  void tick () ;
  
  std::vector<Entity*> getEntities (double xc, double yc, double w, double h) ;
  
	void render (Screen* screen, Camera* camera) ;
  
	bool isFree (Entity* ee, double xc, double yc, int w, int h, double xa, double ya) ;
  
	bool isBulletFree (Entity* bullet, double xc, double yc, int w, int h) ;
  
	void readSign (Sign* sign) ;
  
	void transition (int x, int y) ;
  
	void getGun (int level) ;
  
};

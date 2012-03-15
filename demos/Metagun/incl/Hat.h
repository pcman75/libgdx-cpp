#pragma once
#include "Entity.h"


class Hat : public Entity 
{
public:
	double time;
	int noTakeTime;
	int xPos, yPos;
	double xxa;

public:
  Hat (double x, double y) ;
  
	Hat (double x, double y, int xPos, int yPos) ;
  
	void tick () ;
  
	void render (Screen* g, Camera* camera) ;
  
	bool shot (Bullet* bullet) ;
  
};

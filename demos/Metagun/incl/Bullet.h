#pragma once
#include "Entity.h"
#include "Art.h"
#include "Spark.h"
#include "Level.h"

class Bullet : public Entity 
{
public:
  Entity* source;
	int noHitTime;
	int ntick;

public:
  Bullet( Entity* source, double x, double y, double xa, double ya) ;

	void tick () ;

  void hitWall (double xa, double ya) ;
  
	void render( Screen* g, Camera* camera) ;
  
};

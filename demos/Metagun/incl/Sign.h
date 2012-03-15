#pragma once
#include "Entity.h"

class Sign : public Entity 
{
public:
  int id;
	bool autoRead;

public:
  Sign (int x, int y, int id) ;

	void tick () ;

	void render (Screen* g, Camera* camera) ;

};

#pragma once

#include "Sound.h"
#include "Gdx.h"

class SoundMeta
{
public:
	/*static Sound* boom;
	static Sound* hit;
	static Sound* splat;
	static Sound* launch;
	static Sound* pew;
	static Sound* oof;
	static Sound* gethat;
	static Sound* death;
	static Sound* startgame;
	static Sound* jump;
  */

	static void load () ;
  
	static Sound* load( std::string name) ;
};

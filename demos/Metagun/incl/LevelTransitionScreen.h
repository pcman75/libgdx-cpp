#pragma once
#include "Screen.h"
class Level;
class Camera;

class LevelTransitionScreen : public Screen 
{
private:
  static int TRANSITION_DURATION;
	Level* level1;
	Level* level2;
	int time;
	Screen* parent;
	int xa, ya;
	int xLevel, yLevel;
  Camera* c;

public:
  LevelTransitionScreen (Screen* parent, int xLevel, int yLevel, Level* level1, Level* level2, int xa, int ya) ;

	void tick (InputMeta* input) ;

	void render () ;
};

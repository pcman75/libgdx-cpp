#pragma once
#include "Screen.h"
class GameScreen;

class PauseScreen : public Screen 
{
private:
  GameScreen* parent;
	int selected;
  std::string options[3];

public:
  PauseScreen (GameScreen* parent) ;

	void render () ;
  
	void tick (InputMeta* input) ;
  
};

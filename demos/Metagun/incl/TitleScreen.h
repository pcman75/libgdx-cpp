#pragma once
#include "Screen.h"
class InputMeta;

class TitleScreen : public Screen
{
private:
  int time;

public:
  TitleScreen() ;
  void render () ;
  
	void tick (InputMeta* input) ;
};

#pragma once
#include "Screen.h"

class WinScreen : public Screen 
{
private:
  int time;

public:
  WinScreen();

  void render () ;

	std::string timeHideScale (int val, int time) ;

	std::string timeScale (int val, int time) ;

	void tick (InputMeta* input) ;

};

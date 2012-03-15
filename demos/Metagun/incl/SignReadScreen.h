#pragma once
#include "Screen.h"

class SignReadScreen : public Screen 
{
private:
  Screen* parent;
	std::vector< std::vector<std::string>> signs;
	int delay;
	int id;

public:
  SignReadScreen (Screen* parent, int id) ;

	void render () ;

	void tick (InputMeta* input) ;

};

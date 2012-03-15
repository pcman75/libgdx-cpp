#pragma once
#include "Screen.h"

class ExpositionScreen : public Screen 
{
private:
  int time;
	// "1234567890123456789012345678901234567890"
	std::vector< std::string> lines;

public:
  ExpositionScreen () ;

	void render () ;

	void tick (InputMeta* input) ;
};

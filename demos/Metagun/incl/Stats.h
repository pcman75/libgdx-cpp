#pragma once

class Stats 
{
public:
  static Stats instance;

	int deaths;
	int shots;
	int kills;
	int jumps;
	int time;
	int hats;

private:
  Stats () ;

public:
  static void reset () ;
  
  int getSpeedScore () ;
  
	int getDeathScore () ;
  
	int getHatScore () ;
  
	int getShotScore () ;
  
	int getFinalScore () ;
  
	std::string getTimeString () ;
  
};

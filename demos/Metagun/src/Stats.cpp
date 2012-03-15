#include "stdafx.h"
#include "Stats.h"


Stats Stats::instance;

Stats::Stats () 
{
  deaths = 0;
	shots = 0;
	kills = 0;
	jumps = 0;
  time = 0;
	hats = 0;
}

void Stats::reset () 
{
	Stats::instance = Stats();
}

int Stats::getSpeedScore () 
{
	int seconds = time / 60;
	int speedScore = (60 * 10 - seconds) * 100;
	if (speedScore < 0) speedScore = 0;
	return speedScore;
}

int Stats::getDeathScore () 
{
	int deathScore = 10000 - deaths * 100;
	if (deathScore < 0) deathScore = 0;
	return deathScore;
}

int Stats::getHatScore () 
{
	int hatScore = hats * 5000;
	return hatScore;
}

int Stats::getShotScore () 
{
	return shots / 10;
}

int Stats::getFinalScore () 
{
	return getSpeedScore() + getDeathScore() + getHatScore() + getShotScore();
}

std::string Stats::getTimeString () 
{
	int seconds = time / 60;
	int minutes = seconds / 60;
	seconds %= 60;
	std::string str = minutes + ":";
	if (seconds < 10) str += "0";
	str += seconds;
	return str;
}
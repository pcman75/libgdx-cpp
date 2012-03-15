#pragma once
#include "Screen.h"
class Camera;
class Level;
class InputMeta;

class GameScreen : public Screen 
{
public:
  static int MAX_HATS;
  Level* level;

private:
  static bool DEBUG_MODE;
	int xLevel;
	int yLevel;

	Camera* camera;

	int gunLevel;
	int hatCount;

public:
  bool mayRespawn;

public:
  GameScreen () ;

	void tick (InputMeta* input) ;

	void transition (int xa, int ya) ;

	void render () ;

	void readSign (int id) ;

	void respawnRoom () ;

	void getGun (int level) ;

};

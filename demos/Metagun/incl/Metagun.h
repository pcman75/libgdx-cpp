#pragma once
#include "ApplicationListener.h"

class Screen;
class InputMeta;


class Metagun : public ApplicationListener 
{
public:
	static int GAME_WIDTH;
	static int GAME_HEIGHT;
	static int SCREEN_SCALE;

private:
  static long serialVersionUID;

	bool running;
	Screen* screen;
	InputMeta* input;
	bool started;
	float accum;

public:
  Metagun();

  void create ();
	void pause ();
  void resume ();
  void setScreen (Screen* newScreen);
  void render ();
  virtual void resize (int width, int height);
  virtual void dispose ();
};



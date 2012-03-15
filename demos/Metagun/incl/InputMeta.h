#pragma once
#include "InputProcessor.h"

class InputMeta : public InputProcessor 
{
public:
  static int UP;
	static int DOWN;
	static int LEFT;
	static int RIGHT;

	static int JUMP;
	static int SHOOT;

	static int ESCAPE;

  std::vector<bool> buttons;
	std::vector<bool> oldButtons;

public:
  InputMeta();

  void set (int key, bool down) ;

  void tick () ;

  void releaseAllKeys () ;

  virtual bool keyDown (int keycode) ;

  virtual bool keyUp (int keycode) ;

  virtual bool keyTyped (char character) ;

  virtual bool touchDown (int x, int y, int pointer, int button) ;

  virtual bool touchUp (int x, int y, int pointer, int button) ;

  virtual bool touchDragged (int x, int y, int pointer) ;

  virtual bool touchMoved (int x, int y) ;

  virtual bool scrolled (int amount) ;
  
};

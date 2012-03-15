#include "stdafx.h"
#include "InputMeta.h"
#include "Input.h"
#include "Gdx.h"

int InputMeta::UP = 0;
int InputMeta::DOWN = 1;
int InputMeta::LEFT = 2;
int InputMeta::RIGHT = 3;

int InputMeta::JUMP = 4;
int InputMeta::SHOOT = 5;

int InputMeta::ESCAPE = 6;

InputMeta::InputMeta()
{
  buttons.resize( 64);
  buttons.assign( 64, false);
  oldButtons.resize( 64);
  oldButtons.assign( 64, false);
}
	
void InputMeta::set (int key, bool down) 
{
	int button = -1;

	if (key == Input::Keys::DPAD_UP) button = UP;
	if (key == Input::Keys::DPAD_LEFT) button = LEFT;
	if (key == Input::Keys::DPAD_DOWN) button = DOWN;
	if (key == Input::Keys::DPAD_RIGHT) button = RIGHT;

	if (key == Input::Keys::Y) button = JUMP;
	if (key == Input::Keys::Z) button = JUMP;
	if (key == Input::Keys::X) button = SHOOT;
	if (key == Input::Keys::C) button = JUMP;
	if (key == Input::Keys::A) button = JUMP;
	if (key == Input::Keys::S) button = SHOOT;
	if (key == Input::Keys::D) button = JUMP;

	if (key == Input::Keys::ESCAPE || key == Input::Keys::MENU) button = ESCAPE;

	if (button >= 0) {
		buttons[button] = down;
	}
}

void InputMeta::tick () 
{
	for (int i = 0; i < buttons.size(); i++) 
  {
		oldButtons[i] = buttons[i];
	}

  /*
	if (Gdx.app.getType() == ApplicationType.Android) 
  {
		bool left = false;
		bool right = false;
		bool z = false;
		bool s = false;

		for (int i = 0; i < 2; i++) {
			int x = (int)((Gdx.input.getX(i) / (float)Gdx.graphics.getWidth()) * 320);
			if (!Gdx.input.isTouched(i)) continue;
			if (x < 32) {
				set(Input::Keys::DPAD_LEFT, true);
				left |= true;
			}
			if (x > 32 && x < 90) {
				set(Input::Keys::DPAD_RIGHT, true);
				right |= true;
			}
			if (x > 320 - 64 && x < 320 - 32) {
				set(Input::Keys::Z, true);
				z |= true;
			}
			if (x > 320 - 32 && x < 320) {
				set(Input::Keys::X, true);
				s |= true;
			}
		}

		if (left == false) set(Input::Keys::DPAD_LEFT, false);
		if (right == false) set(Input::Keys::DPAD_RIGHT, false);
		if (z == false) set(Input::Keys::Z, false);
		if (s == false) set(Input::Keys::X, false);
	}
  */
}

void InputMeta::releaseAllKeys () 
{
	for (int i = 0; i < buttons.size(); i++) 
  {
		if (i == UP || i == DOWN) continue;
		buttons[i] = false;
	}
}

bool InputMeta::keyDown (int keycode) 
{
	set(keycode, true);
	return false;
}

bool InputMeta::keyUp (int keycode) 
{
	set(keycode, false);
	return false;
}

bool InputMeta::keyTyped (char character) 
{
	// TODO Auto-generated method stub
	return false;
}

bool InputMeta::touchDown (int x, int y, int pointer, int button) 
{
	return false;
}

bool InputMeta::touchUp (int x, int y, int pointer, int button) 
{
	x = (int)(x / (float)Gdx.graphics->getWidth() * 320);
	if (x > 160 - 32 && x < 160) 
  {
		set(Input::Keys::DPAD_UP, !buttons[UP]);
		if (buttons[UP]) buttons[DOWN] = false;
	}
	if (x > 160 && x < 160 + 32) 
  {
		set(Input::Keys::DPAD_DOWN, !buttons[DOWN]);
		if (buttons[DOWN]) buttons[UP] = false;
	}
	//System.out.println("buttons: " + buttons[UP] + ", " + buttons[DOWN]);
	return false;
}

bool InputMeta::touchDragged (int x, int y, int pointer) 
{
	return false;
}

bool InputMeta::touchMoved (int x, int y) 
{
	return false;
}

bool InputMeta::scrolled (int amount) 
{
	return false;
}

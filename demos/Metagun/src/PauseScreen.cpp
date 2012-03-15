#include "stdafx.h"
#include "PauseScreen.h"
#include "GameScreen.h"
#include "InputMeta.h"
#include "TitleScreen.h"
#include "WinScreen.h"
#include "Art.h"
#include "Level.h"
#include "Player.h"

PauseScreen::PauseScreen (GameScreen* parent) 
{
  options[0] = "BACK TO GAME";
  options[1] = "AUTOMORTIS";
  options[2] = "QUIT TO TITLE";
  selected = 0;
	this->parent = parent;
}

void PauseScreen::render () 
{
	parent->render();

	spriteBatch->begin();
	int xs = 0;
	int ys = 3;
	for (int y = 0; y < 3; y++) 
  {
		int s = options[y].length();
		if (s > xs) xs = s;
	}
	xs += 1;
	int xp = 40;
	int yp = 40;
	for (int x = 0 - 1; x < xs + 1; x++) 
  {
		for (int y = 0 - 1; y < ys + 1; y++) 
    {
			int xf = 1;
			int yf = 12;
			if (x < 0) xf--;
			if (y < 0) yf--;
			if (x >= xs) xf++;
			if (y >= ys) yf++;
			draw( Art::guys[xf][yf], xp + x * 6, yp + y * 6);
		}
	}
	for (int y = 0; y < 3; y++) 
  {
		if (y == selected) 
    {
			drawString("+", xp, yp + y * 6);
		}
		drawString(options[y], xp + 6, yp + y * 6);
	}
	spriteBatch->end();
}

void PauseScreen::tick (InputMeta* input) 
{
	if (!input->oldButtons[InputMeta::ESCAPE] && input->buttons[InputMeta::ESCAPE]) 
  {
		setScreen(parent);
		return;
	}
	if (input->buttons[InputMeta::UP] && !input->oldButtons[InputMeta::UP]) 
  {
		selected--;
		if (selected < 0) selected += 3;
	}
	if (input->buttons[InputMeta::DOWN] && !input->oldButtons[InputMeta::DOWN]) 
  {
		selected++;
		if (selected >= 3) selected -= 3;
	}
	if (input->buttons[InputMeta::SHOOT] && !input->oldButtons[InputMeta::SHOOT]) 
  {
		if (selected == 0) 
    {
			setScreen(parent);
		} 
    else if (selected == 1) 
    {
			parent->level->player->die();
			setScreen(parent);
		} 
    else if (selected == 2) 
    {
			setScreen(new TitleScreen());
		} 
    else if (selected == 3) 
    {
			setScreen(new WinScreen());
		}
	}
	// if (delay>0) delay--;
	// if (delay==0 && input.buttons[Input.SHOOT] && !input.oldButtons[Input.SHOOT]) {
	// setScreen(parent);
	// }
}
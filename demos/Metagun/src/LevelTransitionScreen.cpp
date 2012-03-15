#include "stdafx.h"
#include "LevelTransitionScreen.h"
#include "Camera.h"
#include "Level.h"
#include "Art.h"

int LevelTransitionScreen::TRANSITION_DURATION = 20;

LevelTransitionScreen::LevelTransitionScreen (Screen* parent, int xLevel, int yLevel, Level* level1, Level* level2, int xa, int ya) 
{
  time = 0;
  c = new Camera(320, 240);
	this->level1 = level1;
	this->level2 = level2;
	this->xLevel = xLevel;
	this->yLevel = yLevel;
	this->parent = parent;
	this->xa = xa;
	this->ya = ya;
}

void LevelTransitionScreen::tick (InputMeta* input) 
{
	time++;
	if (time == TRANSITION_DURATION) 
  {
		setScreen(parent);
	}
}

void LevelTransitionScreen::render () 
{
	double pow = time / (double)TRANSITION_DURATION;

	spriteBatch->getTransformMatrix().idt();
	spriteBatch->begin();
// draw(Art.bg, -xLevel * 160 - (int)(xa * 160 * pow), -yLevel * 120 - (int)(ya * 120 * pow));
	draw(&Art::bg, 0, 0);
	spriteBatch->end();

	c->x = (int)(-xa * 320 * pow);
	c->y = (int)(-ya * 240 * pow);
	level1->render(this, c);

	c->x = (int)(xa * 320 * (1 - pow));
	c->y = (int)(ya * 240 * (1 - pow));
	level2->render(this, c);
}
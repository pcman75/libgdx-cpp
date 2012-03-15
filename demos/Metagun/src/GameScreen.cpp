#include "stdafx.h"
#include "GameScreen.h"
#include "Camera.h"
#include "Level.h"
#include "Stats.h"
#include "WinScreen.h"
#include "Art.h"
#include "Player.h"
#include "InputMeta.h"
#include "PauseScreen.h"
#include "LevelTransitionScreen.h"
#include "SignReadScreen.h"

int GameScreen::MAX_HATS = 7;
bool GameScreen::DEBUG_MODE = false;


GameScreen::GameScreen () 
{
  xLevel = DEBUG_MODE ? 8 : 0;
	yLevel = DEBUG_MODE ? 4 : 0;

  level = new Level(this, 32, 24, xLevel, yLevel, 0, 0);
	camera = new Camera(Metagun::GAME_WIDTH, Metagun::GAME_HEIGHT);

	gunLevel = DEBUG_MODE ? 2 : 0;
	hatCount = 1;
  mayRespawn = false;

	Stats::reset();

	level->player->gunLevel = gunLevel;
	level->player->hatCount = hatCount;
}

void GameScreen::tick (InputMeta* input) 
{
	Stats::instance.time++;
	if (!input->oldButtons[InputMeta::ESCAPE] && input->buttons[InputMeta::ESCAPE]) 
  {
		setScreen(new PauseScreen(this));
		return;
	}
	if (!level->player->removed)
		level->player->tick(input);
	else if (mayRespawn) 
  {
		if (input->buttons[InputMeta::SHOOT] && !input->oldButtons[InputMeta::SHOOT]) 
    {
			respawnRoom();
			mayRespawn = false;
		}
	}
	level->tick();
	Stats::instance.hats = level->player->hatCount;
}

void GameScreen::transition (int xa, int ya) 
{
	Stats::instance.hats = level->player->hatCount;
	xLevel += xa;
	yLevel += ya;
	if (yLevel > 10) 
  {
		setScreen(new WinScreen());
		return;
	}
	level->player->x -= xa * 300;
	level->player->y -= ya * 220;
	hatCount = level->player->hatCount;
	if (ya != 0) level->player->y -= 10;
	Level* newLevel = new Level(this, 32, 24, xLevel, yLevel, (int)(level->player->x), (int)(level->player->y + ya * 5));
	newLevel->player->remove();
	newLevel->player = level->player;
	newLevel->add(newLevel->player);
	setScreen(new LevelTransitionScreen(this, xLevel - xa, yLevel - ya, level, newLevel, xa, ya));
	this->level = newLevel;
	level->player->gunLevel = gunLevel;
	level->player->hatCount = hatCount;
	level->player->damage = 0;
}

void GameScreen::render () 
{
	spriteBatch->begin();
// draw(Art.bg, -xLevel * 160, -yLevel * 120);
	draw(&Art::bg, 0, 0);
	spriteBatch->end();
	level->render(this, camera);

	spriteBatch->begin();
	if (mayRespawn) 
  {
		std::string msg = "PRESS X TO TRY AGAIN";
		drawString(msg, 160 - msg.length() * 3, 120 - 3);
	}
	spriteBatch->end();
}

void GameScreen::readSign (int id) 
{
	setScreen( new SignReadScreen(this, id));
}

void GameScreen::respawnRoom () 
{
	Level* newLevel = new Level(this, 32, 24, xLevel, yLevel, level->xSpawn, level->ySpawn);
	this->level = newLevel;
	level->player->gunLevel = gunLevel;
	if (hatCount < 1) hatCount = 1;
	level->player->hatCount = hatCount;
	level->player->damage = 0;
}

void GameScreen::getGun (int level) 
{
	gunLevel = level;
}
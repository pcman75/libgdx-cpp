#include "stdafx.h"
#include "Metagun.h"
#include "WoglApplication.h"
#include "GlfwApplication.h"
#include "InputMeta.h"
#include "Gdx.h"
#include "Art.h"
#include "SoundMeta.h"
#include "TitleScreen.h"
//#include "MainMenuScreen.h"
//#include "Settings.h"
//#include "Assets.h"
#include "GameScreen.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	//WoglApplication( Metagun(), "Metagun", 400, 300, false);
	GlfwApplication( Metagun(), "Metagun", 400, 300, false);
  return 0;
}


int Metagun::GAME_WIDTH = 320;
int Metagun::GAME_HEIGHT = 240;
int Metagun::SCREEN_SCALE = 2;
long Metagun::serialVersionUID = 1L;

Metagun::Metagun()
{
  running = false;
	screen = NULL;
	input = new InputMeta();
	started = false;
	accum = 0;
}

void Metagun::create () 
{
	Art::load();
	SoundMeta::load();
	Gdx.input->setInputProcessor(input);
	running = true;
	setScreen(new TitleScreen());
  //setScreen(new GameScreen());
}

void Metagun::pause () 
{
	running = false;
}

void Metagun::resume () 
{
	running = true;
}

void Metagun::setScreen(Screen* newScreen) 
{
	if (screen != NULL) screen->removed();
	screen = newScreen;
	if (screen != NULL) screen->init(this);
}

void Metagun::render () 
{
	glClear(GL_COLOR_BUFFER_BIT);
	accum += Gdx.graphics->getDeltaTime();
	while (accum > 1.0f / 60.0f) 
  {
		screen->tick(input);
		input->tick();
		accum -= 1.0f / 60.0f;
	}
	screen->render();
// batch.begin();
// font.draw(batch, "fps: " + Gdx.graphics.getFramesPerSecond(), 10, 30);
// batch.end();
}

void Metagun::resize (int width, int height) 
{
	// TODO Auto-generated method stub
}

void Metagun::dispose () 
{
	// TODO Auto-generated method stub
}

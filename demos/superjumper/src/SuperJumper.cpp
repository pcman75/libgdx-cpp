// superjumper.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SuperJumper.h"
#include "MainMenuScreen.h"
#include "Settings.h"
#include "Assets.h"


Screen* SuperJumper::getStartScreen()
{
	return new MainMenuScreen(this);
}

	
void SuperJumper::create()
{
	Settings::load();
	Assets::load();
	Game::create();
}

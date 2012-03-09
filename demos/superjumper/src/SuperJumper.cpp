// superjumper.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SuperJumper.h"
#include "WoglApplication.h"
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


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    WoglApplication(SuperJumper(), "Super Jumper", 320, 480, false);

    return 0;
}


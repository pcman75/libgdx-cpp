#include "stdafx.h"
#include "GdxInvaders.h"
#include "Gdx.h"
#include "MainMenu.h"
//#include "GameLoop.h"
//#include "GameOver.h"


GdxInvaders::GdxInvaders() 
{
	m_isInitialized = false;
}


void GdxInvaders::dispose() 
{
}


void GdxInvaders::render () 
{
	Application* app = Gdx.app;

	// update the screen
	screen->update(app);

	// render the screen
	screen->render(app);

	// when the screen is done we change to the
	// next screen
	if(screen->isDone()) 
	{
		// dispose the current screen
		screen->dispose();

		// if this screen is a main menu screen we switch to
		// the game loop
		if(typeid(screen) == typeid(MainMenu*))
		{
			//screen = new GameLoop(app);
		}
		//else if( typeid(screen) == typeid(GameLoop*))
		{
			// if this screen is a game loop screen we switch to the
			// game over screen	
			//screen = new GameOver(app);
		}
		//else if(typeid(screen) == typeid(GameOver)) 
		{
			screen = new MainMenu(app);
		
		}
	}
}


void GdxInvaders::resize(int width, int height) 
{
}


void GdxInvaders::create () 
{
	if (!m_isInitialized) 
	{
		screen = new MainMenu(Gdx.app);
		Music* music = Gdx.audio->newMusic(Gdx.files->getFileHandle("data/8.12.mp3", Internal));
		music->setLooping(true);
		music->play();
		m_isInitialized = true;
	}
}


void GdxInvaders::pause() 
{
}

void GdxInvaders::resume() 
{
}


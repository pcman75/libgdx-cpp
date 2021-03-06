#include "stdafx.h"
#include "HelpScreen.h"
#include "MainMenuScreen.h"
#include "Assets.h"
#include "OverlapTester.h"
#include "Game.h"

HelpScreen::HelpScreen(Game* game, int helpScreenNumber)
	: Screen(game),	
	m_guiCam(320, 480), m_nextBounds(320 - 64, 0, 64, 64), m_helpScreenNumber(helpScreenNumber)
{
	m_guiCam.position.set(320 / 2, 480 / 2, 0);
	m_helpImage = Assets::loadTexture(getPictureName());
	m_helpRegion = new TextureRegion(m_helpImage, 0, 0, 320, 480);
	m_batcher = new SpriteBatch();
}

HelpScreen::~HelpScreen()
{
	delete m_helpRegion;
	m_helpRegion = NULL;
	delete m_helpImage;
	m_helpImage = NULL;
	delete m_batcher;
	m_batcher = NULL;
}


void HelpScreen::resume() 
{
}

void HelpScreen::pause() 
{
	m_helpImage->dispose();
}

void HelpScreen::update(float deltaTime) 
{
	if (Gdx.input->justTouched()) 
	{
		m_guiCam.unproject(m_touchPoint.set((float)Gdx.input->getX(), (float)Gdx.input->getY(), 0));

		if (OverlapTester::pointInRectangle(m_nextBounds, m_touchPoint.x, m_touchPoint.y)) 
		{
			Assets::playSound(Assets::clickSound);

			if(m_helpScreenNumber < 5)
				m_game->setScreen(new HelpScreen(m_game, m_helpScreenNumber + 1));
			else
				m_game->setScreen(new MainMenuScreen(m_game));
		}
	}
}

void HelpScreen::present(float deltaTime) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	m_guiCam.update();
	m_guiCam.apply();

	glEnable(GL_TEXTURE_2D);

	m_batcher->disableBlending();
	m_batcher->begin();
	m_batcher->draw(m_helpRegion, 0, 0, 320, 480);
	m_batcher->end();

	m_batcher->enableBlending();
	m_batcher->begin();
	m_batcher->draw(Assets::arrow, 320, 0, -64, 64);
	m_batcher->end();

	glDisable(GL_BLEND);
}

const char* HelpScreen::getPictureName()
{
	const char* ret;
	switch(m_helpScreenNumber)
	{
	case 1:
		ret = "data/help1.png";
		break;
	case 2:
		ret = "data/help2.png";
		break;
	case 3:
		ret = "data/help3.png";
		break;
	case 4:
		ret = "data/help4.png";
		break;
	case 5:
		ret = "data/help5.png";
		break;
	}
	return ret;
}

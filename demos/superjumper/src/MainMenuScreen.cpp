#include "stdafx.h"
#include "MainMenuScreen.h"
#include "HighscoresScreen.h"
#include "HelpScreen.h"
#include "OverlapTester.h"
#include "Assets.h"
#include "Settings.h"
#include "Game.h"
#include "GameScreen.h"

MainMenuScreen::MainMenuScreen(Game* game)
	:Screen(game),
	m_soundBounds(0, 0, 64, 64),
	m_playBounds(160 - 150, 200 + 18, 300, 36),
	m_highscoresBounds(160 - 150, 200 - 18, 300, 36),
	m_helpBounds(160 - 150, 200 - 18 - 36, 300, 36)
{
	m_guiCam = new OrthographicCamera(320, 480);
	m_guiCam->position.set(320 / 2, 480 / 2, 0);
	m_batcher = new SpriteBatch();

}

MainMenuScreen::~MainMenuScreen()
{
	delete m_guiCam;
	m_guiCam = NULL;

	m_batcher->dispose();
	
	delete m_batcher;
	m_batcher = NULL;
}

void MainMenuScreen::update(float deltaTime)
{
	if(Gdx.input->justTouched())
	{
		m_guiCam->unproject(m_touchPoint.set(Gdx.input->getX(), Gdx.input->getY(), 0));

		if(OverlapTester::pointInRectangle(m_playBounds, m_touchPoint.x, m_touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			m_game->setScreen(new GameScreen(m_game));
			return;
		}
		if(OverlapTester::pointInRectangle(m_highscoresBounds, m_touchPoint.x, m_touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			m_game->setScreen(new HighscoresScreen(m_game));
			return;
		}
		if(OverlapTester::pointInRectangle(m_helpBounds, m_touchPoint.x, m_touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			m_game->setScreen(new HelpScreen(m_game, 1));
			return;
		}
		if(OverlapTester::pointInRectangle(m_soundBounds, m_touchPoint.x, m_touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			Settings::soundEnabled = !Settings::soundEnabled;
			/*TODO:
			if(Settings::soundEnabled)
				Assets::music->play();
			else
				Assets::music->pause();
				*/
		}
	}
}

void MainMenuScreen::present(float deltaTime)
{
	GLCommon* gl = Gdx.gl;
	gl->glClearColor(1, 0, 0, 1);
	gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
	m_guiCam->update();
	m_batcher->setProjectionMatrix(m_guiCam->combined);

	m_batcher->disableBlending();
	m_batcher->begin();
	m_batcher->draw(Assets::backgroundRegion, 0, 0, 320, 480);
	m_batcher->end();

	m_batcher->enableBlending();
	m_batcher->begin();
	m_batcher->draw(Assets::logo, 160 - 274 / 2, 480 - 10 - 142, 274, 142);
	m_batcher->draw(Assets::mainMenu, 10, (int)(200 - 110 / 2), 300, 110);
	m_batcher->draw(Settings::soundEnabled ? Assets::soundOn : Assets::soundOff, 0, 0, 64, 64);
	m_batcher->end();
}

void MainMenuScreen::pause()
{
	Settings::save();
}

void MainMenuScreen::resume()
{
}

void MainMenuScreen::dispose()
{
}

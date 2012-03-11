#include "stdafx.h"
#include "HighscoresScreen.h"
#include "MainMenuScreen.h"
#include "Settings.h"
#include "Assets.h"
#include "OverlapTester.h"
#include "Game.h"

HighscoresScreen::HighscoresScreen(Game* game) 
	: Screen(game), xOffset(0), guiCam(320, 480), backBounds(0, 0, 64, 64)
{

	batcher = new SpriteBatch();
	guiCam.position.set(320 / 2, 480 / 2, 0);
	for (int i = 0; i < 5; i++) 
	{
		std::stringstream score;
		score << (i + 1) << ". " << Settings::highscores[i];
		highScores[i] = score.str();
		xOffset = max(Assets::font->getBounds(highScores[i]).width, xOffset);
	}
	xOffset = 160 - xOffset / 2 + Assets::font->getSpaceWidth() / 2;
}


void HighscoresScreen::update(float deltaTime) 
{
	if (Gdx.input->justTouched()) 
	{
		guiCam.unproject(touchPoint.set(Gdx.input->getX(), Gdx.input->getY(), 0));

		if (OverlapTester::pointInRectangle(backBounds, touchPoint.x, touchPoint.y)) 
		{
			Assets::playSound(Assets::clickSound);
			m_game->setScreen(new MainMenuScreen(m_game));
			return;
		}
	}
}

void HighscoresScreen::present (float deltaTime) 
{
	GLCommon* gl = Gdx.gl;
	gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
	guiCam.update();
	guiCam.apply(Gdx.gl10);

	gl->glEnable(GL10::GDX_GL_TEXTURE_2D);

	batcher->disableBlending();
	batcher->begin();
	batcher->draw(Assets::backgroundRegion, 0, 0, 320, 480);
	batcher->end();

	batcher->enableBlending();
	batcher->begin();
	batcher->draw(Assets::highScoresRegion, 10, 360 - 16, 300, 33);

	float y = 230;
	for (int i = 4; i >= 0; i--) 
	{
		std:: string highScore = highScores[i];
		Assets::font->draw(batcher, highScore, xOffset, y);
		y += Assets::font->getLineHeight();
	}

	batcher->draw(Assets::arrow, 0, 0, 64, 64);
	batcher->end();
}

void HighscoresScreen::resume() 
{
}


void HighscoresScreen::pause() 
{
}

void HighscoresScreen::dispose() 
{
}

#include "stdafx.h"
#include "HelpScreen.h"
#include "Assets.h"
#include "OverlapTester.h"
#include "Game.h"

HelpScreen::HelpScreen(Game* game)
	: Screen(game),	
	guiCam(320, 480), nextBounds(320 - 64, 0, 64, 64)
{
	helpRegion = new TextureRegion(helpImage, 0, 0, 320, 480);
	guiCam.position.set(320 / 2, 480 / 2, 0);
	helpImage = Assets::loadTexture("data/help1.png");
	batcher = new SpriteBatch();
}

void HelpScreen::resume() 
{
}

void HelpScreen::pause() 
{
	helpImage->dispose();
}

void HelpScreen::update(float deltaTime) 
{
	if (Gdx.input->justTouched()) 
	{
		guiCam.unproject(touchPoint.set(Gdx.input->getX(), Gdx.input->getY(), 0));

		if (OverlapTester::pointInRectangle(nextBounds, touchPoint.x, touchPoint.y)) 
		{
			Assets::playSound(Assets::clickSound);
			//TODO:
			//m_game->setScreen(new HelpScreen2(game));
			return;
		}
	}
}

void HelpScreen::present(float deltaTime) 
{
	GLCommon* gl = Gdx.gl;
	gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
	guiCam.update();
	guiCam.apply(Gdx.gl10);

	gl->glEnable(GL10::GDX_GL_TEXTURE_2D);

	batcher->disableBlending();
	batcher->begin();
	batcher->draw(helpRegion, 0, 0, 320, 480);
	batcher->end();

	batcher->enableBlending();
	batcher->begin();
	batcher->draw(Assets::arrow, 320, 0, -64, 64);
	batcher->end();

	gl->glDisable(GL10::GDX_GL_BLEND);
}


void HelpScreen::dispose() 
{
}


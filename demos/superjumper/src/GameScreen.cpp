#include "stdafx.h"
#include "GameScreen.h"
#include "OverlapTester.h"
#include "Assets.h"
#include "MainMenuScreen.h"
#include "Settings.h"
#include "SoundController.h"

const int GameScreen::GAME_READY = 0;
const int GameScreen::GAME_RUNNING = 1;
const int GameScreen::GAME_PAUSED = 2;
const int GameScreen::GAME_LEVEL_END = 3;
const int GameScreen::GAME_OVER = 4;

GameScreen::GameScreen(Game* game)
	:Screen(game), state(GAME_READY), guiCam(320, 480),
	pauseBounds(320 - 64, 480 - 64, 64, 64), 
	resumeBounds(160 - 96, 240, 192, 36),
	quitBounds(160 - 96, 240 - 36, 192, 36),
	lastScore(0), scoreString("SCORE: 0")
{
	guiCam.position.set(320 / 2, 480 / 2, 0);
	batcher = new SpriteBatch();
	
	worldListener = new SoundController();
	world = new World(worldListener);
	renderer = new WorldRenderer(batcher, world);
}

void GameScreen::update(float deltaTime)
{
	if(deltaTime > 0.1f) deltaTime = 0.1f;

	switch(state)
	{
	case GAME_READY:
		updateReady();
		break;
	case GAME_RUNNING:
		updateRunning(deltaTime);
		break;
	case GAME_PAUSED:
		updatePaused();
		break;
	case GAME_LEVEL_END:
		updateLevelEnd();
		break;
	case GAME_OVER:
		updateGameOver();
		break;
	}
}

void GameScreen::updateReady()
{
	if(Gdx.input->justTouched())
	{
		state = GAME_RUNNING;
	}
}

void GameScreen::updateRunning(float deltaTime)
{
	if(Gdx.input->justTouched())
	{
		guiCam.unproject(touchPoint.set(Gdx.input->getX(), Gdx.input->getY(), 0));

		if(OverlapTester::pointInRectangle(pauseBounds, touchPoint.x, touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			state = GAME_PAUSED;
			return;
		}
	}

	if(Gdx.app->getType() == Application::Android)
	{
		world->update(deltaTime, Gdx.input->getAccelerometerX());
	}
	else
	{
		float accel = 0;
		if(Gdx.input->isKeyPressed(Input::Keys::DPAD_LEFT)) 
			accel = 5.f;
		if(Gdx.input->isKeyPressed(Input::Keys::DPAD_RIGHT)) 
			accel = -5.f;
		world->update(deltaTime, accel);
	}
	if(world->score != lastScore)
	{
		lastScore = world->score;
		scoreString = "SCORE: " + lastScore;
	}
	if(world->state == World::WORLD_STATE_NEXT_LEVEL)
	{
		state = GAME_LEVEL_END;
	}
	if(world->state == World::WORLD_STATE_GAME_OVER)
	{
		state = GAME_OVER;
		if(lastScore >= Settings::highscores[4])
			scoreString = "NEW HIGHSCORE: " + lastScore;
		else
			scoreString = "SCORE: " + lastScore;
		Settings::addScore(lastScore);
		Settings::save();
	}
}

void GameScreen::updatePaused()
{
	if(Gdx.input->justTouched())
	{
		guiCam.unproject(touchPoint.set(Gdx.input->getX(), Gdx.input->getY(), 0));

		if(OverlapTester::pointInRectangle(resumeBounds, touchPoint.x, touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			state = GAME_RUNNING;
			return;
		}

		if(OverlapTester::pointInRectangle(quitBounds, touchPoint.x, touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			m_game->setScreen(new MainMenuScreen(m_game));
			return;

		}
	}
}

void GameScreen::updateLevelEnd()
{
	if(Gdx.input->justTouched())
	{
		world = new World(worldListener);
		renderer = new WorldRenderer(batcher, world);
		world->score = lastScore;
		state = GAME_READY;
	}
}

void GameScreen::updateGameOver()
{
	if(Gdx.input->justTouched())
	{
		m_game->setScreen(new MainMenuScreen(m_game));
	}
}

void GameScreen::present(float deltaTime)
{
	GLCommon* gl = Gdx.gl;
	gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
	gl->glEnable(GL10::GDX_GL_TEXTURE_2D);

	renderer->render();

	guiCam.update();
	batcher->setProjectionMatrix(guiCam.combined);
	batcher->enableBlending();
	batcher->begin();
	switch(state)
	{
	case GAME_READY:
		presentReady();
		break;
	case GAME_RUNNING:
		presentRunning();
		break;
	case GAME_PAUSED:
		presentPaused();
		break;
	case GAME_LEVEL_END:
		presentLevelEnd();
		break;
	case GAME_OVER:
		presentGameOver();
		break;
	}
	batcher->end();
}

void GameScreen::presentReady()
{
	batcher->draw(Assets::ready, 160 - 192 / 2, 240 - 32 / 2, 192, 32);
}

void GameScreen::presentRunning()
{
	batcher->draw(Assets::pause, 320 - 64, 480 - 64, 64, 64);
	Assets::font->draw(batcher, scoreString, 16, 480 - 20);
}

void GameScreen::presentPaused()
{
	batcher->draw(Assets::pauseMenu, 160 - 192 / 2, 240 - 96 / 2, 192, 96);
	Assets::font->draw(batcher, scoreString, 16, 480 - 20);
}

void GameScreen::presentLevelEnd()
{
	std::string topText = "the princess is ...";
	std::string bottomText = "in another castle!";
	float topWidth = Assets::font->getBounds(topText).width;
	float bottomWidth = Assets::font->getBounds(bottomText).width;
	Assets::font->draw(batcher, topText, 160 - topWidth / 2, 480 - 40);
	Assets::font->draw(batcher, bottomText, 160 - bottomWidth / 2, 40);
}

void GameScreen::presentGameOver()
{
	batcher->draw(Assets::gameOver, 160 - 160 / 2, 240 - 96 / 2, 160, 96);
	float scoreWidth = Assets::font->getBounds(scoreString).width;
	Assets::font->draw(batcher, scoreString, 160 - scoreWidth / 2, 480 - 20);
}

void GameScreen::pause()
{
	if(state == GAME_RUNNING) 
		state = GAME_PAUSED;
}

void GameScreen::resume()
{
}

void GameScreen::dispose()
{
}


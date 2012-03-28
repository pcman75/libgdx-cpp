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
	:Screen(game), m_state(GAME_READY), m_guiCam(320, 480),
	m_pauseBounds(320 - 64, 480 - 64, 64, 64), 
	m_resumeBounds(160 - 96, 240, 192, 36),
	m_quitBounds(160 - 96, 240 - 36, 192, 36),
	m_lastScore(0), m_scoreString("SCORE: 0")
{
	m_guiCam.position.set(320 / 2, 480 / 2, 0);
	m_batcher = new SpriteBatch();
	
	m_worldListener = new SoundController();
	m_world = new World(m_worldListener);
	m_renderer = new WorldRenderer(m_batcher, m_world);
}

void GameScreen::update(float deltaTime)
{
	if(deltaTime > 0.1f) 
		deltaTime = 0.1f;

	switch(m_state)
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
		m_state = GAME_RUNNING;
	}
}

void GameScreen::updateRunning(float deltaTime)
{
	if(Gdx.input->justTouched())
	{
		m_guiCam.unproject(m_touchPoint.set(Gdx.input->getX(), Gdx.input->getY(), 0));

		if(OverlapTester::pointInRectangle(m_pauseBounds, m_touchPoint.x, m_touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			m_state = GAME_PAUSED;
			return;
		}
	}

	if(Gdx.app->getType() == Application::Android)
	{
		m_world->update(deltaTime, Gdx.input->getAccelerometerX());
	}
	else
	{
		float accel = 0;
		if(Gdx.input->isKeyPressed(Input::Keys::DPAD_LEFT)) 
			accel = 5.f;
		if(Gdx.input->isKeyPressed(Input::Keys::DPAD_RIGHT)) 
			accel = -5.f;
		m_world->update(deltaTime, accel);
	}
	if(m_world->score != m_lastScore)
	{
		m_lastScore = m_world->score;
		std::stringstream scoreFormat;
		scoreFormat << "SCORE: " << m_lastScore;
		m_scoreString = scoreFormat.str();
	}
	if(m_world->state == World::WORLD_STATE_NEXT_LEVEL)
	{
		m_state = GAME_LEVEL_END;
	}
	if(m_world->state == World::WORLD_STATE_GAME_OVER)
	{
		std::stringstream scoreFormat;
		
		m_state = GAME_OVER;
		if(m_lastScore >= Settings::highscores[4])
			scoreFormat << "NEW HIGHSCORE: " << m_lastScore;
		else
			scoreFormat << "SCORE: " << m_lastScore;

		m_scoreString = scoreFormat.str();
		Settings::addScore(m_lastScore);
		Settings::save();
	}
}

void GameScreen::updatePaused()
{
	if(Gdx.input->justTouched())
	{
		m_guiCam.unproject(m_touchPoint.set(Gdx.input->getX(), Gdx.input->getY(), 0));

		if(OverlapTester::pointInRectangle(m_resumeBounds, m_touchPoint.x, m_touchPoint.y))
		{
			Assets::playSound(Assets::clickSound);
			m_state = GAME_RUNNING;
			return;
		}

		if(OverlapTester::pointInRectangle(m_quitBounds, m_touchPoint.x, m_touchPoint.y))
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
		m_world = new World(m_worldListener);
		m_renderer = new WorldRenderer(m_batcher, m_world);
		m_world->score = m_lastScore;
		m_state = GAME_READY;
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
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);

	m_renderer->render();

	m_guiCam.update();
	m_batcher->setProjectionMatrix(m_guiCam.combined);
	m_batcher->enableBlending();
	m_batcher->begin();
	switch(m_state)
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
	m_batcher->end();
}

void GameScreen::presentReady()
{
	m_batcher->draw(Assets::ready, 160 - 192 / 2, 240 - 32 / 2, 192, 32);
}

void GameScreen::presentRunning()
{
	m_batcher->draw(Assets::pause, 320 - 64, 480 - 64, 64, 64);
	Assets::font->draw(m_batcher, m_scoreString, 16, 480 - 20);
}

void GameScreen::presentPaused()
{
	m_batcher->draw(Assets::pauseMenu, 160 - 192 / 2, 240 - 96 / 2, 192, 96);
	Assets::font->draw(m_batcher, m_scoreString, 16, 480 - 20);
}

void GameScreen::presentLevelEnd()
{
	std::string topText = "the princess is ...";
	std::string bottomText = "in another castle!";
	float topWidth = Assets::font->getBounds(topText).width;
	float bottomWidth = Assets::font->getBounds(bottomText).width;
	Assets::font->draw(m_batcher, topText, 160 - topWidth / 2, 480 - 40);
	Assets::font->draw(m_batcher, bottomText, 160 - bottomWidth / 2, 40);
}

void GameScreen::presentGameOver()
{
	m_batcher->draw(Assets::gameOver, 160 - 160 / 2, 240 - 96 / 2, 160, 96);
	float scoreWidth = Assets::font->getBounds(m_scoreString).width;
	Assets::font->draw(m_batcher, m_scoreString, 160 - scoreWidth / 2, 480 - 20);
}

void GameScreen::pause()
{
	if(m_state == GAME_RUNNING) 
		m_state = GAME_PAUSED;
}

void GameScreen::resume()
{
}

GameScreen::~GameScreen()
{
	m_batcher->dispose();
	delete m_batcher;
	m_batcher = NULL;
	
	delete m_worldListener;
	m_worldListener = NULL;

	delete m_world;
	m_world = NULL;
	
	delete m_renderer;
	m_renderer = NULL;
}


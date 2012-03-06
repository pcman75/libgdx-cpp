#include "stdafx.h"
#include "Screen.h"
#include "Game.h"
#include "Gdx.h"


void Game::setScreen(Screen* helpScreen2)
{
	m_screen->pause();
	m_screen->dispose();
	delete m_screen;
	m_screen = helpScreen2;
}


void Game::create()
{
	m_screen = getStartScreen();
}

void Game::resume()
{
	m_screen->resume();
}

void Game::render()
{
	m_screen->update(Gdx.graphics->getDeltaTime());
	m_screen->present(Gdx.graphics->getDeltaTime());
}

void Game::resize(int width, int height)
{

}


void Game::pause()
{
	m_screen->pause();
}

void Game::dispose()
{
	m_screen->dispose();
}


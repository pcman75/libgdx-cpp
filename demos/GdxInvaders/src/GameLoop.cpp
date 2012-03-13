#include "stdafx.h"
#include "GameLoop.h"

GameLoop::GameLoop(Application* app)
	: m_renderer(app)
{
	m_simulation.listener = this;
	m_explosion = app->getAudio()->newSound(app->getFiles()->getFileHandle("data/explosion.ogg", Internal));
	m_shot = app->getAudio()->newSound(app->getFiles()->getFileHandle("data/shot.ogg", Internal));
}

void GameLoop::dispose ()
{
	m_renderer.dispose();
	m_shot->dispose();
	m_explosion->dispose();
}

bool GameLoop::isDone ()
{
	return m_simulation.ship.lives == 0;
}

void GameLoop::render(Application* app)
{
	app->getGraphics()->getGL10()->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT | GL10::GDX_GL_DEPTH_BUFFER_BIT);
	m_renderer.render(app, &m_simulation);
}

void GameLoop::update(Application* app)
{
	m_simulation.update(app->getGraphics()->getDeltaTime());

	Input* input = app->getInput();
	if (input->getAccelerometerY() < 0)
		m_simulation.moveShipLeft(app->getGraphics()->getDeltaTime(), fabs(input->getAccelerometerY()) / 10);
	else
		m_simulation.moveShipRight(app->getGraphics()->getDeltaTime(), fabs(input->getAccelerometerY()) / 10);

	if (input->isKeyPressed(Input::Keys::DPAD_LEFT)) 
		m_simulation.moveShipLeft(app->getGraphics()->getDeltaTime(), 0.5f);
	if (input->isKeyPressed(Input::Keys::DPAD_RIGHT)) 
		m_simulation.moveShipRight(app->getGraphics()->getDeltaTime(), 0.5f);

	if (input->isTouched() || input->isKeyPressed(Input::Keys::SPACE)) 
		m_simulation.shot();
}

void GameLoop::explosion ()
{
	m_explosion->play();
}

void GameLoop::shot ()
{
	m_shot->play();
}


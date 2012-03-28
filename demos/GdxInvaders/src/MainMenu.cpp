#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu(Application* app)
{
	m_isDone = false;
	m_spriteBatch = new SpriteBatch();
	m_background = new Texture(Gdx.files->internalHandle("data/planet.jpg"));
	m_background->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);

	m_logo = new Texture(Gdx.files->internalHandle("data/title.png"));
	m_logo->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);

	m_font = new BitmapFont(Gdx.files->internalHandle("data/font16.fnt"), Gdx.files->internalHandle("data/font16.png"), false);
}

void MainMenu::render(Application* app)
{
	m_viewMatrix.setToOrtho2D(0, 0, 480, 320);
	m_spriteBatch->setProjectionMatrix(m_viewMatrix);
	m_spriteBatch->setTransformMatrix(m_transformMatrix);
	m_spriteBatch->begin();
	m_spriteBatch->disableBlending();
	m_spriteBatch->setColor(Color::WHITE);
	m_spriteBatch->draw(m_background, 0, 0, 480, 320, 0, 0, 512, 512, false, false);
	m_spriteBatch->enableBlending();
	m_spriteBatch->draw(m_logo, 0, 320 - 128, 480, 128, 0, 0, 512, 256, false, false);
	m_spriteBatch->setBlendFunction(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	std::string text = "Touch screen to start!";
	float width = m_font->getBounds(text).width;
	m_font->draw(m_spriteBatch, text, 240 - width / 2, 128);
	m_spriteBatch->end();
}

void MainMenu::update(Application* app)
{
	m_isDone = app->getInput()->isTouched();
}

bool MainMenu::isDone()
{
	return m_isDone;
}

void MainMenu::dispose()
{
	m_spriteBatch->dispose();
	m_background->dispose();
	m_logo->dispose();
	m_font->dispose();
}

MainMenu::~MainMenu()
{
	//TODO:
	//delete some pointers
}

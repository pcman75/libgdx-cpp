#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver(Application* app)
	: m_isDone(false)
{
	m_spriteBatch = new SpriteBatch();
	m_background = new Texture(Gdx.files->internalHandle("data/planet.jpg"));
	m_background->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);

	m_logo = new Texture(Gdx.files->internalHandle("data/title.png"));
	m_logo->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);

	m_font = new BitmapFont(Gdx.files->internalHandle("data/font16.fnt"), Gdx.files->internalHandle("data/font16.png"), false);
}

void GameOver::dispose()
{
	m_spriteBatch->dispose();
	m_background->dispose();
	m_logo->dispose();
	m_font->dispose();
}

bool GameOver::isDone()
{
	return m_isDone;
}

void GameOver::render(Application* app)
{
	m_viewMatrix.setToOrtho2D(0, 0, 480, 320);
	m_spriteBatch->setProjectionMatrix(m_viewMatrix);
	m_spriteBatch->setTransformMatrix(m_transformMatrix);
	m_spriteBatch->begin();
	m_spriteBatch->disableBlending();
	m_spriteBatch->setColor(Color::WHITE);
	m_spriteBatch->draw(m_background, 0, 0, 480, 320, 0, 0, 512, 512, false, false);
	m_spriteBatch->enableBlending();
	m_spriteBatch->draw(m_logo, 0, 320 - 128, 480, 128, 0, 256, 512, 256, false, false);
	std::string text = "It is the end my friend.\nTouch to continue!";
	BitmapFont::TextBounds bounds = m_font->getMultiLineBounds(text);
	m_spriteBatch->setBlendFunction(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	m_font->drawMultiLine(m_spriteBatch, text, 0, 160 + bounds.height / 2, 480, BitmapFont::CENTER);
	m_spriteBatch->end();
}

void GameOver::update(Application* app)
{
	m_isDone = app->getInput()->isTouched();
}



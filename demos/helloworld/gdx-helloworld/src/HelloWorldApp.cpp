#include "StdAfx.h"
#include "HelloWorldApp.h"
#include "Color.h"

HelloWorldApp::HelloWorldApp(void)
	: textPosition(100, 100), textDirection(1, 1)
{
}


HelloWorldApp::~HelloWorldApp(void)
{
}

void HelloWorldApp::create () 
{
		//font = new BitmapFont();
		font = new BitmapFont(Gdx.files->internalHandle("data/default.fnt"), false);
		font->setColor(Color::RED);
		texture = new Texture(Gdx.files->internalHandle("data/badlogic.jpg"));
		spriteBatch = new SpriteBatch();
}

void HelloWorldApp::render () 
{
		int centerX = Gdx.graphics->getWidth() / 2;
		int centerY = Gdx.graphics->getHeight() / 2;

		glClear(GL_COLOR_BUFFER_BIT);

		// more fun but confusing :)
		// textPosition.add(textDirection.tmp().mul(Gdx.graphics.getDeltaTime()).mul(60));
		textPosition.x += textDirection.x * Gdx.graphics->getDeltaTime() * 60;
		textPosition.y += textDirection.y * Gdx.graphics->getDeltaTime() * 60;

		if (textPosition.x < 0) 
		{
			textDirection.x = -textDirection.x;
			textPosition.x = 0;
		}
		if (textPosition.x > Gdx.graphics->getWidth()) 
		{
			textDirection.x = -textDirection.x;
			textPosition.x = Gdx.graphics->getWidth();
		}
		if (textPosition.y < 0) 
		{
			textDirection.y = -textDirection.y;
			textPosition.y = 0;
		}
		if (textPosition.y > Gdx.graphics->getHeight()) 
		{
			textDirection.y = -textDirection.y;
			textPosition.y = Gdx.graphics->getHeight();
		}

		spriteBatch->begin();
		spriteBatch->setColor(Color::WHITE);
		spriteBatch->draw(texture, centerX - texture->getWidth() / 2, centerY - texture->getHeight() / 2, 0, 0, texture->getWidth(),
			texture->getHeight());
		font->draw(spriteBatch, "Hello World!", (int)textPosition.x, (int)textPosition.y);
		spriteBatch->end();
	}

	void HelloWorldApp::resize (int width, int height) 
	{
		spriteBatch->getProjectionMatrix().setToOrtho2D(0, 0, width, height);
		textPosition.set(0, 0);
	}


void HelloWorldApp::pause (){}

void HelloWorldApp::resume (){}

void HelloWorldApp::dispose ()
{
	delete font;
	delete spriteBatch;
}

#pragma once
#include "applicationlistener.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "BitmapFont.h"
#include "Vector2.h"

class HelloWorldApp :
	public ApplicationListener
{
private:
	SpriteBatch* spriteBatch;
	Texture* texture;
	BitmapFont* font;
	Vector2 textPosition;
	Vector2 textDirection;

public:
	HelloWorldApp(void);
	virtual ~HelloWorldApp(void);

	virtual void create ();
	virtual void resize (int width, int height);
	virtual void render ();
	virtual void pause ();
	virtual void resume ();
	virtual void dispose ();
};


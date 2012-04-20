#pragma once
#include "GdxTest.h"
#include "Pixmap.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "TextureRegion.h"
#include "Sprite.h"

//#include "Input.h"

class SpriteBatchTest : 
	public GdxTest
{
private:
	int SPRITES;
	int frames;
	Texture* texture;
	Texture* texture2;
	// Font font;
	SpriteBatch* spriteBatch;
	std::vector<float> sprites;
	std::vector<float> sprites2;
	Sprite* sprites3;
	float angle;
	float ROTATION_SPEED;
	float scale;
	float SCALE_SPEED;
	int renderMethod;
    Timer* timer;

public:
	SpriteBatchTest();
	virtual ~SpriteBatchTest();

	GDX_DEFINE_CREATOR(SpriteBatchTest);

	virtual void render();
	virtual void renderNormal();

	virtual void renderSprites();
	virtual void create ();
	virtual void resize(int width, int height);

	virtual bool keyDown (int keycode);
	virtual bool keyTyped (char character);
	virtual bool keyUp (int keycode);
	virtual bool touchDown (int x, int y, int pointer, int newParam);
	virtual bool touchDragged (int x, int y, int pointer);
	virtual bool touchUp (int x, int y, int pointer, int button);
	virtual bool touchMoved (int x, int y);
	virtual bool scrolled (int amount);
};

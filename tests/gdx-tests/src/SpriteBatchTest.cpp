#include "stdafx.h"
#include "SpriteBatchTest.h"
#include <time.h>

long nTime = 0;
long nanoTime()
{
	nTime += 10000;
	return nTime;
}

SpriteBatchTest::SpriteBatchTest()
{
	// init random numbers
	//
	srand( (unsigned)time( NULL ) );


	spriteBatch = NULL;

	SPRITES = 100 / 2;
	startTime = nanoTime();
	frames = 0;

	texture = texture2 = NULL;

	//sprites = new float[SPRITES * 6];
	//sprites2 = new float[SPRITES * 6];
	sprites.resize( SPRITES * 6);
	sprites2.resize( SPRITES * 6);

	sprites3 = new Sprite[SPRITES * 2];
	angle = 0;
	ROTATION_SPEED = 20;
	scale = 1;
	SCALE_SPEED = -1;

	renderMethod = 0;
}
SpriteBatchTest::~SpriteBatchTest()
{
}

void SpriteBatchTest::render() 
{
	if (renderMethod == 0) 
		renderNormal();
	if (renderMethod == 1) 
		renderSprites();
}

void SpriteBatchTest::renderNormal() 
{
	GL10* gl = Gdx.gl10;
	gl->glClearColor(0.7f, 0.7f, 0.7f, 1);
	gl->glClear( GL10::GDX_GL_COLOR_BUFFER_BIT);

	float begin = 0;
	float end = 0;
	float draw1 = 0;
	float draw2 = 0;
	float drawText = 0;

	angle += ROTATION_SPEED * Gdx.graphics->getDeltaTime();
	scale += SCALE_SPEED * Gdx.graphics->getDeltaTime();
	if (scale < 0.5f) {
		scale = 0.5f;
		SCALE_SPEED = 1;
	}
	if (scale > 1.0f) {
		scale = 1.0f;
		SCALE_SPEED = -1;
	}

	long start = nanoTime();
	spriteBatch->begin();
	begin = (nanoTime() - start) / 1000000000.0f;


	start = nanoTime();
	for (int i = 0; i < sprites.size(); i += 6)
		spriteBatch->draw( texture, sprites[i], sprites[i + 1], 16, 16, 32, 32, scale, scale, angle, 0, 0, 32, 32, false, false);
	draw1 = (nanoTime() - start) / 1000000000.0f;

	start = nanoTime();
	for (int i = 0; i < sprites2.size(); i += 6)
		spriteBatch->draw( texture2, sprites2[i], sprites2[i + 1], 16, 16, 32, 32, scale, scale, angle, 0, 0, 32, 32, false, false);
	draw2 = (nanoTime() - start) / 1000000000.0f;

	start = nanoTime();
	// spriteBatch->drawText(font, "Question?", 100, 300, Color.RED);
	// spriteBatch->drawText(font, "and another this is a test", 200, 100, Color.WHITE);
	// spriteBatch->drawText(font, "all hail and another this is a test", 200, 200, Color.WHITE);
	// spriteBatch->drawText(font, "normal fps: " + Gdx.graphics->getFramesPerSecond(), 10, 30, Color.RED);
	drawText = (nanoTime() - start) / 1000000000.0f;

	start = nanoTime();
	spriteBatch->end();
	end = (nanoTime() - start) / 1000000000.0f;

	if (nanoTime() - startTime > 1000000000) 
	{
		/*
		std::stringstream stream;
		stream << "SpriteBatch";
		stream << "fps: ";
		stream <<  frames;
		stream << ", render calls: ";
		stream << spriteBatch->renderCalls;
		stream << ", ";
		stream << begin;
		stream << ", ";
		stream << draw1;
		stream << ", ";
		stream << draw2;
		stream << ", ";
		stream << drawText;
		stream << ", ";
		stream << end;
		frames = 0;
		startTime = nanoTime();
		Gdx.app->log( L"Sprite", stream);
		*/
	}
	frames++;
}


void SpriteBatchTest::renderSprites () 
{
	GL10* gl = Gdx.gl10;
	gl->glClearColor(0.7f, 0.7f, 0.7f, 1);
	gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);

	float begin = 0;
	float end = 0;
	float draw1 = 0;
	float draw2 = 0;
	float drawText = 0;

	long start = nanoTime();
	spriteBatch->begin();
	begin = (nanoTime() - start) / 1000000000.0f;

	float angleInc = ROTATION_SPEED * Gdx.graphics->getDeltaTime();
	scale += SCALE_SPEED * Gdx.graphics->getDeltaTime();
	if (scale < 0.5f) {
		scale = 0.5f;
		SCALE_SPEED = 1;
	}
	if (scale > 1.0f) {
		scale = 1.0f;
		SCALE_SPEED = -1;
	}

	start = nanoTime();
	for (int i = 0; i < SPRITES; i++) 
	{
		if (angleInc != 0) sprites3[i].rotate(angleInc); // this is aids
		if (scale != 1) sprites3[i].setScale(scale); // this is aids
		sprites3[i].draw( spriteBatch);
	}
	draw1 = (nanoTime() - start) / 1000000000.0f;

	start = nanoTime();
	for (int i = SPRITES; i < SPRITES << 1; i++) {
		if (angleInc != 0) sprites3[i].rotate(angleInc); // this is aids
		if (scale != 1) sprites3[i].setScale(scale); // this is aids
		sprites3[i].draw( spriteBatch);
	}

	draw2 = (nanoTime() - start) / 1000000000.0f;

	start = nanoTime();
	// spriteBatch->drawText(font, "Question?", 100, 300, Color.RED);
	// spriteBatch->drawText(font, "and another this is a test", 200, 100, Color.WHITE);
	// spriteBatch->drawText(font, "all hail and another this is a test", 200, 200, Color.WHITE);
	// spriteBatch->drawText(font, "Sprite fps: " + Gdx.graphics->getFramesPerSecond(), 10, 30, Color.RED);
	drawText = (nanoTime() - start) / 1000000000.0f;

	start = nanoTime();
	spriteBatch->end();
	end = (nanoTime() - start) / 1000000000.0f;

	if (nanoTime() - startTime > 1000000000) 
	{
		/*
		Gdx.app.log("SpriteBatch", "fps: " + frames + ", render calls: " + spriteBatch->renderCalls + ", " + begin + ", " + draw1
		+ ", " + draw2 + ", " + drawText + ", " + end);
		*/
		frames = 0;
		startTime = nanoTime();
	}
	frames++;
}

void SpriteBatchTest::create () 
{
	spriteBatch = new SpriteBatch( 1000);

	Pixmap* pixmap = new Pixmap(Gdx.files->internalHandle("data/badlogicsmall.jpg"));

	texture = new Texture( 32, 32, Pixmap::Format::RGB565);
	texture->setFilter( Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);
	texture->draw( pixmap, 0, 0);
	pixmap->dispose();

	Pixmap* pixmap2 = new Pixmap(32, 32, Pixmap::Format::RGBA8888);
	pixmap2->setColor(1, 1, 0, 0.5f);
	pixmap2->fill();
	texture2 = new Texture( pixmap2);
	pixmap2->dispose();

	// font = Gdx.graphics->newFont("Arial", 32, FontStyle.Plain);

	for (int i = 0; i < sprites.size(); i += 6) {
		sprites[i] = (int)(MathUtils::randomFloat() * (Gdx.graphics->getWidth() - 32));
		sprites[i + 1] = (int)(MathUtils::randomFloat() * (Gdx.graphics->getHeight() - 32));
		sprites[i + 2] = 0;
		sprites[i + 3] = 0;
		sprites[i + 4] = 32;
		sprites[i + 5] = 32;
		sprites2[i] = (int)(MathUtils::randomFloat() * (Gdx.graphics->getWidth() - 32));
		sprites2[i + 1] = (int)(MathUtils::randomFloat() * (Gdx.graphics->getHeight() - 32));
		sprites2[i + 2] = 0;
		sprites2[i + 3] = 0;
		sprites2[i + 4] = 32;
		sprites2[i + 5] = 32;
	}

	for (int i = 0; i < SPRITES * 2; i++) {
		int x = (int)(MathUtils::randomFloat() * (Gdx.graphics->getWidth() - 32));
		int y = (int)(MathUtils::randomFloat() * (Gdx.graphics->getHeight() - 32));

		if (i >= SPRITES)
			sprites3[i] = new Sprite( texture2, 32, 32);
		else
			sprites3[i] = new Sprite( texture, 32, 32);
		sprites3[i].setPosition(x, y);
		sprites3[i].setOrigin(16, 16);
	}

	//Gdx.input->setInputProcessor(this);
	//Gdx.input = dynamic_cast< Input*> this;

}



void SpriteBatchTest::resize(int width, int height) 
{
	std::stringstream message;
	message << "resized: " << width << ", " << height;
	Gdx.app->log("SpriteBatchTest", message.str().c_str());
}

bool SpriteBatchTest::keyDown (int keycode) 
{
	return false;
}

bool SpriteBatchTest::keyTyped (char character) 
{
	return false;
}

bool SpriteBatchTest::keyUp (int keycode) 
{
	return false;
}

bool SpriteBatchTest::touchDown (int x, int y, int pointer, int newParam) 
{
	return false;
}

bool SpriteBatchTest::touchDragged (int x, int y, int pointer) 
{
	return false;
}

bool SpriteBatchTest::touchUp (int x, int y, int pointer, int button) 
{
	renderMethod = (renderMethod + 1) % 2;
	return false;
}

bool SpriteBatchTest::touchMoved (int x, int y) 
{
	return false;
}

bool SpriteBatchTest::scrolled (int amount) 
{
	return false;
}

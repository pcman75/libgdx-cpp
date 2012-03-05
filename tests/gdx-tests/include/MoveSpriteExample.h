#pragma once

#include "GdxTest.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "OrthographicCamera.h"

/**
 * Demonstrates how to let a sprite follow a finger touching the
 * screen.
 */

class MoveSpriteExample :
	public GdxTest
{
	Texture* texture;
	SpriteBatch* batch;
	OrthographicCamera* camera;
	Vector3 spritePosition;

public:
	MoveSpriteExample()
	{
		texture = NULL;
		batch = NULL;
		camera = NULL;
	}

	~MoveSpriteExample()
	{
		delete texture;
		delete batch;
		delete camera;
		texture = NULL;
		batch = NULL;
		camera = NULL;
	}

	void create()
	{
		// create a SpriteBatch with which to render the sprite
		batch = new SpriteBatch();

		// load the sprite's texture. note: usually you have more than
		// one sprite in a texture, see {@see TextureAtlas} and {@see TextureRegion}.
		texture = new Texture(Gdx.files->internalHandle("data/bobargb8888-32x32.png"));

		// create an {@link OrthographicCamera} which is used to transform
		// touch coordinates to world coordinates.
		camera = new OrthographicCamera();

		// we want the camera to setup a viewport with pixels as units, with the
		// y-axis pointing upwards. The origin will be in the lower left corner
		// of the screen.
		camera->setToOrtho(false);
	}

	void render()
	{
		// set the clear color and clear the screen.
		Gdx.gl->glClearColor(1, 1, 1, 1);
		Gdx.gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);

		// draw the sprite
		batch->begin();
		batch->draw(texture, spritePosition.x, spritePosition.y);
		batch->end();

		// if a finger is down, set the sprite's x/y coordinate.
		if(Gdx.input->isTouched())
		{
			// the unproject method takes a Vector3 in window coordinates (origin in
			// upper left corner, y-axis pointing down) and transforms it to world
			// coordinates.
			camera->unproject(spritePosition.set(Gdx.input->getX(), Gdx.input->getY(), 0));
		}
	}

	GDX_DEFINE_CREATOR(MoveSpriteExample);
};

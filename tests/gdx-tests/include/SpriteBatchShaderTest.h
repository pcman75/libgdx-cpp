/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#pragma once
#include "GdxTest.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "Color.h"
#include "Timer.h"

class SpriteBatchShaderTest :
	public GdxTest
{
	static const int SPRITES = 400;

	long startTime;
	int frames;

	Texture* texture;
	Texture* texture2;
	// Font font;
	SpriteBatch* spriteBatch;
	int coords[SPRITES * 2];
	int coords2[SPRITES * 2];

	Color col;

	Mesh* mesh;
	float vertices[SPRITES * 6 * (2 + 2 + 4)];
	Timer* timer;

public:
	~SpriteBatchShaderTest()
	{
		delete texture;
		delete texture2;
		delete spriteBatch;
		delete mesh;
		delete timer;
	}

	SpriteBatchShaderTest():
		frames(0), col(1, 1, 1, 0.6f),
		texture(0), texture2(0), spriteBatch(0), mesh(0), timer(0)
	{
	}

	void render()
	{
		
		glClearColor(0.7f, 0.7f, 0.7f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		float begin = 0;
		float end = 0;
		float draw1 = 0;
		float draw2 = 0;
		float drawText = 0;

		timer->startTimer();
		spriteBatch->begin();
		begin = timer->stopTimer();

		int len = sizeof(coords) / sizeof(coords[0]);
		
		timer->startTimer();
		for(int i = 0; i < len; i += 2)
			spriteBatch->draw(texture, coords[i], coords[i + 1], 0, 0, 32, 32);
		draw1 = timer->stopTimer();

		timer->startTimer();
		spriteBatch->setColor(col);
		int len2 = sizeof(coords2) / sizeof(coords2[0]);
		for(int i = 0; i < len2; i += 2)
			spriteBatch->draw(texture2, coords2[i], coords2[i + 1], 0, 0, 32, 32);
		draw2 = timer->stopTimer();

		timer->startTimer();
// spriteBatch.drawText(font, "Question?", 100, 300, Color.RED);
// spriteBatch.drawText(font, "and another this is a test", 200, 100, Color.WHITE);
// spriteBatch.drawText(font, "all hail and another this is a test", 200, 200, Color.WHITE);
		drawText = timer->stopTimer();

		timer->startTimer();
		spriteBatch->end();
		end = timer->stopTimer();

		//if(end > 1000000000)
		{
			std::stringstream logText;
			logText << "fps: " << frames << ", render calls: " << spriteBatch->renderCalls << ", " << begin << ", " << draw1
			            << ", " << draw2 << ", " << drawText << ", " << end;
			Gdx.app->log("SpriteBatch", logText.str().c_str());
			frames = 0;
		}
		frames++;
	}

	void create()
	{
		timer = Gdx.app->createTimer();

		spriteBatch = new SpriteBatch();
		Pixmap* pixmap = new Pixmap(Gdx.files->internalHandle("data/badlogicsmall.jpg"));
// pixmap.setColor( 0, 0, 0, 0 );
// pixmap.fillCircle( 16, 16, 4 );
		texture = new Texture(32, 32, Pixmap::Format::RGB565);
		texture->draw(pixmap, 0, 0);
		pixmap->dispose();

		pixmap = new Pixmap(32, 32, Pixmap::Format::RGB565);
		pixmap->setColor(1, 1, 0, 0.7f);
		pixmap->fill();
// pixmap.setColor( 0, 0, 0, 0 );
// pixmap.fillCircle( 16, 16, 4 );
//
		texture2 = new Texture(pixmap);
		pixmap->dispose();

// if (font == null) font = Gdx.graphics.newFont("Arial", 32, FontStyle.Plain);
		int len = sizeof(coords) / sizeof(coords[0]);
		for(int i = 0; i < len; i += 2)
		{
			coords[i] = MathUtils::random(Gdx.graphics->getWidth());
			coords[i + 1] = MathUtils::random(Gdx.graphics->getHeight());
			coords2[i] = MathUtils::random(Gdx.graphics->getWidth());
			coords2[i + 1] = MathUtils::random(Gdx.graphics->getHeight());
		}
	}

	virtual bool needsGL20()
	{
		return true;
	}

	GDX_DEFINE_CREATOR(SpriteBatchShaderTest);
};

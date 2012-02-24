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

public:
	SpriteBatchShaderTest():
		frames(0), col(1, 1, 1, 0.6f)
	{
		long startTime = System.nanoTime();
	}

	void render()
	{
		GL20* gl = Gdx.graphics->getGL20();
		gl->glClearColor(0.7f, 0.7f, 0.7f, 1);
		gl->glClear(GL20::GDX_GL_COLOR_BUFFER_BIT);

		float begin = 0;
		float end = 0;
		float draw1 = 0;
		float draw2 = 0;
		float drawText = 0;

		long start = System.nanoTime();
		spriteBatch.begin();
		begin = (System.nanoTime() - start) / 1000000000.0f;

		int len = coords.length;
		start = System.nanoTime();
		for(int i = 0; i < len; i += 2)
			spriteBatch.draw(texture, coords[i], coords[i + 1], 0, 0, 32, 32);
		draw1 = (System.nanoTime() - start) / 1000000000.0f;

		start = System.nanoTime();
		spriteBatch.setColor(col);
		for(int i = 0; i < coords2.length; i += 2)
			spriteBatch.draw(texture2, coords2[i], coords2[i + 1], 0, 0, 32, 32);
		draw2 = (System.nanoTime() - start) / 1000000000.0f;

		start = System.nanoTime();
// spriteBatch.drawText(font, "Question?", 100, 300, Color.RED);
// spriteBatch.drawText(font, "and another this is a test", 200, 100, Color.WHITE);
// spriteBatch.drawText(font, "all hail and another this is a test", 200, 200, Color.WHITE);
		drawText = (System.nanoTime() - start) / 1000000000.0f;

		start = System.nanoTime();
		spriteBatch.end();
		end = (System.nanoTime() - start) / 1000000000.0f;

		if(System.nanoTime() - startTime > 1000000000)
		{
			Gdx.app.log("SpriteBatch", "fps: " + frames + ", render calls: " + spriteBatch.renderCalls + ", " + begin + ", " + draw1
			            + ", " + draw2 + ", " + drawText + ", " + end);
			frames = 0;
			startTime = System.nanoTime();
		}
		frames++;
	}

	void create()
	{
		spriteBatch = new SpriteBatch();
		Pixmap pixmap = new Pixmap(Gdx.files.internal("data/badlogicsmall.jpg"));
// pixmap.setColor( 0, 0, 0, 0 );
// pixmap.fillCircle( 16, 16, 4 );
		texture = new Texture(32, 32, Format.RGB565);
		texture.draw(pixmap, 0, 0);
		pixmap.dispose();

		pixmap = new Pixmap(32, 32, Format.RGB565);
		pixmap.setColor(1, 1, 0, 0.7f);
		pixmap.fill();
// pixmap.setColor( 0, 0, 0, 0 );
// pixmap.fillCircle( 16, 16, 4 );
//
		texture2 = new Texture(pixmap);
		pixmap.dispose();

// if (font == null) font = Gdx.graphics.newFont("Arial", 32, FontStyle.Plain);

		for(int i = 0; i < coords.length; i += 2)
		{
			coords[i] = (int)(Math.random() * Gdx.graphics.getWidth());
			coords[i + 1] = (int)(Math.random() * Gdx.graphics.getHeight());
			coords2[i] = (int)(Math.random() * Gdx.graphics.getWidth());
			coords2[i + 1] = (int)(Math.random() * Gdx.graphics.getHeight());
		}
	}
};

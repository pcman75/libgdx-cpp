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

#include "SpriteBatch.h"
#include "GdxTest.h"
#include "BitmapFont.h"
#include "ImmediateModeRenderer10.h"

class BitmapFontTest :
	public GdxTest
{
private:
	SpriteBatch* spriteBatch;
	
	BitmapFont* font;
	ImmediateModeRenderer10* renderer;

	
public:
	void create()
	{
		spriteBatch = new SpriteBatch();

		//TextureAtlas textureAtlas = new TextureAtlas("data/pack");
		//font = new BitmapFont(Gdx.files.internal("data/verdana39.fnt"), textureAtlas.findRegion("verdana39"), false);
		//font = new BitmapFont(Gdx.files->internalHandle("data/verdana39.fnt"), textureAtlas->findRegion("verdana39"), false);
		renderer = new ImmediateModeRenderer10();
		font = new BitmapFont(Gdx.files->internalHandle("data/default.fnt"), false);
	}

	void render()
	{
		// red.a = (red.a + Gdx.graphics.getDeltaTime() * 0.1f) % 1;

		int viewHeight = Gdx.graphics->getHeight();

		GL10* gl = Gdx.graphics->getGL10();
		gl->glClearColor(0, 1, 1, 1);
		gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
		spriteBatch->begin();

		std::string text = "Sphinx of black quartz, judge my vow.";
		font->setColor(Color::RED);

		float x = 100, y = 20;
		float alignmentWidth;

		if(false)
		{
			alignmentWidth = 0;
			font->drawMultiLine(spriteBatch, text, x, viewHeight - y, alignmentWidth, BitmapFont::RIGHT);
		}

		if(false)
		{
			BitmapFont::TextBounds& bounds = font->getMultiLineBounds(text);
			alignmentWidth = bounds.width;
			font->drawMultiLine(spriteBatch, text, x, viewHeight - y, alignmentWidth, BitmapFont::RIGHT);
		}

		if(true)
		{
			alignmentWidth = 280;
			//font->drawMultiLine(spriteBatch, text, x, viewHeight - y, alignmentWidth, BitmapFont::RIGHT);
			font->drawWrapped(spriteBatch, text, x, viewHeight - y, alignmentWidth, BitmapFont::LEFT);
		}

		spriteBatch->end();

		drawRect(x, viewHeight - y, x + alignmentWidth, 300);
	}

	void drawRect(float x1, float y1, float x2, float y2)
	{
		renderer->begin(GL10::GDX_GL_LINE_STRIP);
		renderer->vertex(x1, y1, 0);
		renderer->vertex(x1, y2, 0);
		renderer->vertex(x2, y2, 0);
		renderer->vertex(x2, y1, 0);
		renderer->vertex(x1, y1, 0);
		renderer->end();
	}

	~BitmapFontTest()
	{
		delete font;
		delete spriteBatch;
		delete renderer;
	}

	GDX_DEFINE_CREATOR(BitmapFontTest);
};

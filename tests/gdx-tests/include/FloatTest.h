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

class FloatTest :
	public GdxTest
{

	Texture* tex;
	Texture* tex2;
	float* vertices;
	static const int BYTES_PER_VERTEX = (4 + 3 + 2 + 2) * 4;
	float angle;
	float angleIncrement;

public:
	FloatTest()
	{
		tex = NULL;
		tex2 = NULL;
		vertices = NULL;
		angle = 0;
		angleIncrement = 0.1f;

	}
	~FloatTest()
	{
		tex->dispose();
		tex2->dispose();

		delete[] vertices;
		delete tex;
		delete tex2;
	}

	void render()
	{
		GL10* gl = Gdx.graphics->getGL10();
		gl->glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		gl->glClearColor(0.7f, 0.7f, 0.7f, 1);
		gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
		gl->glMatrixMode(GL10::GDX_GL_MODELVIEW);
		gl->glLoadIdentity();	
		gl->glRotatef(angle, 0, 0, 1);
		angle += angleIncrement;
		gl->glEnable(GL10::GDX_GL_TEXTURE_2D);

		gl->glEnableClientState(GL10::GDX_GL_COLOR_ARRAY);
		gl->glColorPointer(4, GL10::GDX_GL_FLOAT, BYTES_PER_VERTEX, vertices);

		gl->glEnableClientState(GL10::GDX_GL_TEXTURE_COORD_ARRAY);
		gl->glClientActiveTexture(GL10::GDX_GL_TEXTURE0);
		gl->glActiveTexture(GL10::GDX_GL_TEXTURE0);
		tex->bind();
		gl->glTexCoordPointer(2, GL10::GDX_GL_FLOAT, BYTES_PER_VERTEX, vertices + 4);

		gl->glClientActiveTexture(GL10::GDX_GL_TEXTURE1);
		gl->glActiveTexture(GL10::GDX_GL_TEXTURE1);
		tex2->bind();
		gl->glTexCoordPointer(2, GL10::GDX_GL_FLOAT, BYTES_PER_VERTEX, vertices + 6);

		gl->glEnableClientState(GL10::GDX_GL_VERTEX_ARRAY);
		gl->glVertexPointer(3, GL10::GDX_GL_FLOAT, BYTES_PER_VERTEX, vertices + 8);

		gl->glDrawArrays(GL10::GDX_GL_TRIANGLES, 0, 3);
	}

private:
	void init()
	{
		if(tex != NULL)
		{
			tex->dispose();
			tex2->dispose();

			delete tex;
			delete tex2;
			tex = NULL;
			tex2 = NULL;
		}

		vertices = new float[(BYTES_PER_VERTEX * 3)/sizeof(float)];
		float verts[] = {1., 0., 0, 1, 0, 1, 0, 1, -0.5f, -0.5f, 0,
		                 0, 1, 0, 1, 1, 1, 1, 1, 0.5f, -0.5f, 0,
		                 0, 0, 1, 1, 0.5f, 0, 0.5f, 0, 0, 0.5f, 0,
		                };
		memcpy(vertices, verts, sizeof(verts));

		Pixmap* pixmap = new Pixmap(256, 256, Pixmap::Format::RGBA8888);
		pixmap->setColor(1, 1, 1, 1);
		pixmap->fill();
		pixmap->setColor(0, 0, 0, 1);
		pixmap->drawLine(0, 0, 256, 256);
		pixmap->drawLine(256, 0, 0, 256);
		tex = new Texture(pixmap, false);
		//pixmap->dispose();
		//delete pixmap;

		pixmap = new Pixmap(256, 256, Pixmap::Format::RGBA8888);
		pixmap->setColor(1, 1, 1, 1);
		pixmap->fill();
		pixmap->setColor(0, 0, 0, 1);
		pixmap->drawLine(128, 0, 128, 256);
		tex2 = new Texture(pixmap, false);
		//pixmap->dispose();
		//delete pixmap;
	}

public:
	void create()
	{
		init();
	}

	void resume()
	{
		init();
	}

	GDX_DEFINE_CREATOR(FloatTest);
};
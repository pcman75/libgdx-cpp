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
#include "ApplicationListener.h"

class AlphaTest  :
	public ApplicationListener
{
	SpriteBatch* m_batch;
	Texture* m_texture;

public:
	void create () 
	{
		Pixmap* pixmap = new Pixmap(256, 256, Pixmap::Format::RGBA8888);
		pixmap->setColor(0, 1, 0, 0.7f);
		pixmap->fill();

		m_texture = new Texture(pixmap, false);
		m_texture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);
		m_batch = new SpriteBatch();
		pixmap->dispose();

		//TODO: pixamp cannot be fully destroyed!!!
		//delete pixmap;
	}

	void render () {
		Gdx.graphics->getGL10()->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);

		m_batch->begin();
		m_batch->draw(m_texture, 0, 0, 256, 256, 0, 0, 256, 256, false, false);
		m_batch->end();
	}

	//TODO: note necessary. remove them after implementing Test base class
	virtual void resize (int width, int height) {}
	virtual void pause () {}
	virtual void resume () {}
	virtual void dispose () {}
};

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

#include "SpriteBatch.h"
#include "Texture.h"
#include "ApplicationListener.h"

class TextureDataTest  :
	public ApplicationListener
{
private:
	SpriteBatch* m_spriteBatch;
	Texture* m_texture;

public:
	void create () 
	{
		m_spriteBatch = new SpriteBatch();
		m_texture = new Texture(new PixmapTextureData(new Pixmap(Gdx.files->internalHandle("c:\\t8890.png")), Pixmap::Format::Unknown, false, true));
		//m_texture = new Texture(new FileTextureData(Gdx.files->internalHandle("c:\\t8890.png"), NULL, Pixmap::Format::Unknown, false));
	}

	void render () 
	{
		m_spriteBatch->begin();
		m_spriteBatch->draw(m_texture, 100, 100);
		m_spriteBatch->end();
	}

	//TODO: note necessary. remove them after implementing Test base class
	virtual void resize (int width, int height) {}
	virtual void pause () {}
	virtual void resume () {}
	virtual void dispose () {}
};

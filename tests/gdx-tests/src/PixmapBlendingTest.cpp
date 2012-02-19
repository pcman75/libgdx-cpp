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
#include "stdafx.h"
#include "PixmapBlendingTest.h"
#include "GdxRuntimeException.h"
#include "PixmapIO.h"

PixmapBlendingTest::PixmapBlendingTest()
{
}

PixmapBlendingTest::~PixmapBlendingTest()
{
}

void PixmapBlendingTest::create() 
{
	
	m_spriteBatch = new SpriteBatch();

	Matrix4 transform;
	transform.setToTranslation(0, Gdx.graphics->getHeight(), 0);
	transform.mul(Matrix4().setToScaling(1, -1, 1));
	m_spriteBatch->setTransformMatrix(transform);
	
	m_pixS1 = new Pixmap(Gdx.files->internalHandle("data/test4.png"));
	m_pixS2 = new Pixmap(Gdx.files->internalHandle("data/test3.png"));
	m_pixD = new Pixmap(64, 128, Pixmap::Format::RGBA8888);

	m_pixD->drawPixmap(m_pixS1, 0, 0, 0, 0, 76, 76);
	m_pixD->drawPixmap(m_pixS2, 0, 0, 0, 0, 76, 76);
	PixmapIO::writePNG(Gdx.files->getFileHandle("data/debug.png", Internal), m_pixD);
	
	m_logoSprite = new Sprite(new Texture(m_pixD));
	m_logoSprite->flip(false, true);

	m_pixS1->dispose();
	m_pixS2->dispose();
	m_pixD->dispose();	
	
}

void PixmapBlendingTest::render()
{
	GL10* gl = Gdx.graphics->getGL10();
	//gl->glClearColor(0, 1, 0, 1);
	Gdx.gl->glClearColor(0.6f, 0.6f, 0.6f, 1);
	gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);

	m_spriteBatch->begin();
	m_logoSprite->draw(m_spriteBatch);
	m_spriteBatch->end();
	
}
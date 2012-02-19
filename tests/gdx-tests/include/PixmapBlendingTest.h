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

#include "SpriteBatch.h"
#include "Texture.h"
#include "Sprite.h"
#include "Pixmap.h"

class PixmapBlendingTest  :
	public GdxTest 
{
public:
	PixmapBlendingTest();
	virtual ~PixmapBlendingTest();

	virtual void create();
	virtual void render();

	GDX_DEFINE_CREATOR(PixmapBlendingTest);

private: 
	SpriteBatch* m_spriteBatch;
	Texture* m_text;
	Sprite* m_logoSprite;
	Sprite* m_test3;
	Sprite* m_test4;
	Pixmap* m_pixD;
	Pixmap* m_pixS1;
	Pixmap* m_pixS2;
};

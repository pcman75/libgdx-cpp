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
#include "TextureRegion.h"
#include "SpriteBatch.h"

class RotationTest :
	public GdxTest
{
private:
	Texture* texture;
	TextureRegion* region;
	SpriteBatch* batch;

public:
	void create ()
	{
		texture = new Texture(Gdx.files->internalHandle("data/black_marked_0.png"));
		region = new TextureRegion(texture);
		batch = new SpriteBatch();
		batch->getTransformMatrix().setToTranslation(30.5f, 30.5f, 0);
	}

	void render ()
	{
		Gdx.gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
		batch->begin();
		batch->draw(texture, 0, 0);
		batch->draw(region, 128, 0, 64, 64, 128, 128, 1, 1, 90);
		batch->draw(region, 128, 128, 64, 64, 128, 128, 1, 1, 180);
		batch->draw(region, 0, 128, 64, 64, 128, 128, 1, 1, 270);
		batch->end();
	}

	GDX_DEFINE_CREATOR(RotationTest);
};

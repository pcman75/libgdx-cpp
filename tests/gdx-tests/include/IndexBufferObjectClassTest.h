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
#include "GdxTest.h"
#include "Texture.h"
#include "VertexBufferObject.h"
#include "IndexBufferObject.h"
#include "Color.h"

class IndexBufferObjectClassTest :
	public GdxTest
{
	Texture* texture;
	VertexBufferObject* vbo;
	IndexBufferObject* ibo;

public:
	~IndexBufferObjectClassTest()
	{
		texture->dispose();
		vbo->dispose();
		ibo->dispose();
		delete texture;
		delete vbo;
		delete ibo;
		texture = NULL;
		vbo = NULL;
		ibo = NULL;
	}

	void render()
	{
		
		glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);
		texture->bind();
		vbo->bind();
		ibo->bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
		ibo->unbind();
		vbo->unbind();
	}

	void create()
	{
		VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 2, "a_Position"),
			VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_TexCoords"), 
			VertexAttribute(VertexAttributes::ColorPacked, 4, "a_Color")};
		vbo = new VertexBufferObject(true, attributes, 3);
		float vertices[] = {-1, -1, 0, 0, Color::toFloatBits(1.f, 0.f, 0.f, 1.f), 0, 1, 0.5f, 1.0f,
		                                Color::toFloatBits(0.f, 1.f, 0.f, 1.f), 1, -1, 1, 0, Color::toFloatBits(0.f, 0.f, 1.f, 1.f)
		                               };
		vbo->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));

		ibo = new IndexBufferObject(true);

		short indices[] = {0, 1, 2};
		ibo->setIndices(indices, 3);

		texture = new Texture(Gdx.files->internalHandle("data/badlogic.jpg"));
	}

	void resume()
	{
		vbo->invalidate();
		ibo->invalidate();
	}
	GDX_DEFINE_CREATOR(IndexBufferObjectClassTest);
};

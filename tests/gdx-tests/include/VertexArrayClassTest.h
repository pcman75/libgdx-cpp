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
#include "VertexArray.h"
//#include "Color.h"



class VertexArrayClassTest :
	public GdxTest
{
	Texture* m_texture;
	VertexArray* m_va;
	short* m_indices;

public:
	~VertexArrayClassTest()
	{
		m_texture->dispose();
		m_va->dispose();
		delete m_texture;
		delete m_va;
	}

	void render ()
	{
	
		glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);
		m_texture->bind();
		m_va->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.5f, 0.5f, 0);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, m_indices);
		glPopMatrix();
		m_va->unbind();
	}

	void create()
	{
		VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 2, "a_Position"),
			VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_TexCoords"), 
			VertexAttribute(VertexAttributes::ColorPacked, 4, "a_Color")};

		m_va = new VertexArray(attributes, 3);
		float vertices[] = { -1, -1, 0, 0, Color::toFloatBits(1.f, 0.f, 0.f, 1.f), 
			0, 1, 0.5f, 1.0f, Color::toFloatBits(0.f, 1.f, 0.f, 1.f), 
			1, -1, 1, 0, Color::toFloatBits(0.f, 0.f, 1.f, 1.f)};

		m_va->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
		
		m_indices = new short[3];
		m_indices[0] = 0; m_indices[1] = 1; m_indices[2] = 2;

		m_texture = new Texture(Gdx.files->internalHandle("data/badlogic.jpg"));
	}

	GDX_DEFINE_CREATOR(VertexArrayClassTest);
};

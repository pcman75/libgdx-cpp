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
#include "Mesh.h"
#include "Texture.h"

class MeshTest :
	public GdxTest
{
	Mesh* m_mesh;
	Texture* m_texture;

public:
	void render()
	{
		Gdx.graphics->getGL10()->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
		Gdx.graphics->getGL10()->glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		Gdx.graphics->getGL10()->glEnable(GL10::GDX_GL_TEXTURE_2D);
		m_texture->bind();
		m_mesh->render(GL10::GDX_GL_TRIANGLES);//, 0, 6);
	}

	void create()
	{
		VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 3, "a_position"), VertexAttribute(VertexAttributes::ColorPacked, 4,
			"a_color"), VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_texCoords")};
		m_mesh = new Mesh(true, attributes, 3);

		float vertices[] = {-0.5f, -0.5f, 0, Color::toFloatBits(255, 0, 0, 255), 0, 0, 0.5f, -0.5f, 0,
		                              Color::toFloatBits(0, 255, 0, 255), 1, 0, 0.5f, 0.5f, 0, Color::toFloatBits(0, 0, 255, 255), 1.f, 1, -0.5f, 0.5f, 0,
		                              Color::toFloatBits(255, 255, 255, 255), 0, 1 };
		m_mesh->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));

		short indices[] = {0, 1, 2, 2, 3, 0};
		m_mesh->setIndices(indices, sizeof(indices)/sizeof(indices[0]));

		m_texture = new Texture(Gdx.files->internalHandle("data/badlogic.jpg"), true);
		m_texture->setFilter(Texture::TextureFilter::MipMap, Texture::TextureFilter::Linear);
	}

	GDX_DEFINE_CREATOR(MeshTest);
};

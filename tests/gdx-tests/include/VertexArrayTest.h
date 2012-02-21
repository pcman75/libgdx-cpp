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
#include "Gdx.h"

class VertexArrayTest :
	public GdxTest
{
private:
	float* m_vertices;
	short* m_indices;

public:
	void render()
	{
		const int BYTES_PER_VERTEX = (3 + 4) * 4;

		GL10* gl = Gdx.graphics->getGL10();
		gl->glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		gl->glClearColor(0.7f, 0.7f, 0.7f, 1);
		gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);

		gl->glEnableClientState(GL10::GDX_GL_COLOR_ARRAY);
		//m_vertices.position(3);
		gl->glColorPointer(4, GL10::GDX_GL_FLOAT, BYTES_PER_VERTEX, m_vertices + 3);

		gl->glEnableClientState(GL10::GDX_GL_VERTEX_ARRAY);
		//vertices.position(0);
		gl->glVertexPointer(3, GL10::GDX_GL_FLOAT, BYTES_PER_VERTEX, m_vertices);

		gl->glDrawElements(GL10::GDX_GL_TRIANGLES, 3, GL10::GDX_GL_UNSIGNED_SHORT, m_indices);
	}

	
	void create ()
	{
		float vertices[] = { -0.5f, -0.5f, 0, 1, 0, 0, 0,
		                  0.5f, -0.5f, 0, 0, 1, 0, 0,
		                  0, 0.5f, 0, 0, 0, 1, 0
		                };
		int numVertices = sizeof(vertices) / sizeof(vertices[0]);
		m_vertices = new float[numVertices];
		memcpy(m_vertices, vertices, numVertices * sizeof(float));

		short indices[] = {0, 1, 2};
		m_indices = new short[3];
		memcpy(m_indices, indices, 3 * sizeof(short));
	}
	~VertexArrayTest()
	{
		delete[] m_vertices;
		m_vertices = NULL;
		delete[] m_indices;
		m_indices = NULL;
	}

	GDX_DEFINE_CREATOR(VertexArrayTest);
};

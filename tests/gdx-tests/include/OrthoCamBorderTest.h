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

#include "Mesh.h"
#include "GdxTest.h"

#include "OrthographicCamera.h"
#include "Rectang.h"

class OrthoCamBorderTest :
	public GdxTest
{

	static const int WIDTH = 480;
	static const int HEIGHT = 320;
	
	OrthographicCamera m_cam;
	Rectang m_glViewport;
	Mesh* m_mesh;

public:
	GDX_DEFINE_CREATOR(OrthoCamBorderTest);	
	void create()
	{
		VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 2, "a_pos"), VertexAttribute(VertexAttributes::Color, 4, "a_col")};
		m_mesh = new Mesh(true, attributes, 2);
		float vertices[] = {
			0, 0, 1, 0, 0, 1, 
			WIDTH, 0,  0, 1, 0, 1, 
			WIDTH, HEIGHT, 0, 0, 1, 1, 
			0, HEIGHT, 1, 0, 1, 1};
		
		m_mesh->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
		short indices[] = {0, 1, 2, 2, 3, 0};
		m_mesh->setIndices(indices, sizeof(indices)/sizeof(indices[0]));

		m_cam = OrthographicCamera(WIDTH, HEIGHT);
		m_cam.position.set(WIDTH / 2, HEIGHT / 2, 0);

		m_glViewport = calculateGLViewport(WIDTH, HEIGHT);
	}

private:
	Rectang calculateGLViewport(int desiredWidth, int desiredHeight)
	{
		Rectang viewport;
		if (Gdx.graphics->getWidth() > Gdx.graphics->getHeight())
		{
			float aspect = (float)Gdx.graphics->getHeight() / desiredHeight;
			viewport.width = desiredWidth * aspect;
			viewport.height = Gdx.graphics->getHeight();
			viewport.x = Gdx.graphics->getWidth() / 2 - viewport.width / 2;
			viewport.y = 0;
		}
		else
		{
			float aspect = (float)Gdx.graphics->getWidth() / desiredWidth;
			viewport.width = Gdx.graphics->getWidth();
			viewport.height = desiredHeight * aspect;
			viewport.x = 0;
			viewport.y = Gdx.graphics->getHeight() / 2 - viewport.height / 2;
		}
		return viewport;
	}

public:
	void resize(int width, int height)
	{
		m_glViewport = calculateGLViewport(WIDTH, HEIGHT);
	}

	void render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport((int)m_glViewport.x, (int)m_glViewport.y, (int)m_glViewport.width, (int)m_glViewport.height);

		m_cam.update();
		m_cam.apply();
		m_mesh->render(GL_TRIANGLES);
	}
};

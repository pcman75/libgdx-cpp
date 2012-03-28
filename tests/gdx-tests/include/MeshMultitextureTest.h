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

#include "GdxTest.h"
#include "Texture.h"
#include "Mesh.h"

class MeshMultitextureTest :
	public GdxTest
{
private:
	Texture* tex1;
	Texture* tex2;
	Mesh* mesh;

public:
	
	void render()
	{
		
		glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		tex1->bind();

		glActiveTexture(GL_TEXTURE1);
		glEnable(GL_TEXTURE_2D);
		tex2->bind();
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
		glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_ADD);

		mesh->render(GL_TRIANGLES);
	}

	void create()
	{
		VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 3, "a_Position"),
			VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_texCoords1"), 
			VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_texCoords2")};
		mesh = new Mesh(true, attributes, 3);

		float vertices[] = {-0.5f, -0.5f, 0, 0, 1, 0, 1, 0.5f, -0.5f, 0, 1, 1, 1, 1, 0.5f, 0.5f, 0, 1, 0, 1, 0, -0.5f, 0.5f, 0, 0, 0, 0, 0};
		mesh->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
		short indices[] = {0, 1, 2, 2, 3, 0};
		mesh->setIndices(indices, sizeof(indices)/sizeof(indices[0]));

		tex1 = new Texture(Gdx.files->internalHandle("data/planet_earth.png"));
		tex2 = new Texture(Gdx.files->internalHandle("data/planet_heavyclouds.jpg"));
	}

	GDX_DEFINE_CREATOR(MeshMultitextureTest);
};

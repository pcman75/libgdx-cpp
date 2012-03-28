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

class BobTest :
	public GdxTest
{
	class Bob
	{
	public:
		float x, y;
		float dirX, dirY;

	public:
		Bob()
		{
			x = MathUtils::randomFloat(320.);
			y = MathUtils::randomFloat(480.);
			dirX = 10;
			dirY = 10;
		}
		void update(float deltaTime)
		{
			x = x + dirX * deltaTime;
			y = y + dirY * deltaTime;

			if(x < 0)
			{
				dirX = -dirX;
				x = 0;
			}

			if(x > 320)
			{
				dirX = -dirX;
				x = 320;
			}

			if(y < 0)
			{
				dirY = -dirY;
				y = 0;
			}

			if(y > 480)
			{
				dirY = -dirY;
				y = 480;
			}
		}
	};

	static const int NUM_BOBS = 100;
	Texture* bobTexture;
	Mesh* bobModel;
	Bob bobs[NUM_BOBS];

public:
	void create()
	{
		bobTexture = new Texture(Gdx.files->internalHandle("data/bobargb8888-32x32.png"));

		VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 2, "a_pos"),
			VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_tex")};
		bobModel = new Mesh(true, attributes, 2);
		float vertices[] = {-16, -16, 0, 1, 16, -16, 1, 1, 16, 16, 1, 0, -16, 16, 0, 0,};
		bobModel->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
		short indices[] = {0, 1, 2, 2, 3, 0};
		bobModel->setIndices(indices, sizeof(indices)/sizeof(indices[0]));
		bobModel->setAutoBind(false);
	}

	void render()
	{
		float deltaTime = min(Gdx.graphics->getDeltaTime(), 0.1f);
		for(int i = 0; i < NUM_BOBS; i++)
		{
			bobs[i].update(deltaTime);
		}

		glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 320, 0, 480, 1, -1);

		glMatrixMode(GL_MODELVIEW);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		bobTexture->bind();

		bobModel->bind();
		for(int i = 0; i < NUM_BOBS; i++)
		{
			glLoadIdentity();
			glTranslatef((int)(bobs[i].x + 0.5), (int)(bobs[i].y + 0.5), 0);		
			bobModel->render(GL_TRIANGLES, 0, 6);
		}
		bobModel->unbind();
	}

	GDX_DEFINE_CREATOR(BobTest);	
};

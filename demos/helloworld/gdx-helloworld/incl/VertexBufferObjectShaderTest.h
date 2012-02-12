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

#include "ApplicationListener.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "VertexBufferObject.h"

class VertexBufferObjectShaderTest : public ApplicationListener
{
private:
	Texture* m_texture;
	ShaderProgram* m_shader;
	VertexBufferObject* m_vbo;
	short* m_indices;

	template<class T> 
	void clean(T*& pointer)
	{
		if(pointer)
		{
			pointer->dispose();
			delete pointer;
			pointer = NULL;
		}
	}

public:
	void dispose();
	void render();
	void create ();
	void resume ();

	//TODO: not necessary. remove them after implementing Test base class
	virtual void resize (int width, int height) {}
	virtual void pause () {}
};

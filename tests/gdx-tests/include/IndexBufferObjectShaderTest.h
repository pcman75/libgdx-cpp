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
#include "ShaderProgram.h"
#include "VertexBufferObject.h"
#include "IndexBufferObject.h"

class IndexBufferObjectShaderTest :
	public GdxTest
{
private:
	Texture* texture;
	ShaderProgram* shader;
	VertexBufferObject* vbo;
	IndexBufferObject* ibo;

public:
	virtual bool needsGL20()
	{
		return true;
	}

	void dispose()
	{
		texture->dispose();
		shader->dispose();
		ibo->dispose();
		delete texture;
		delete shader;
		delete ibo;
		texture = NULL;
		shader = NULL;
		ibo = NULL;
	}


	void render()
	{
		GL20* gl = Gdx.gl20;
		gl->glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		gl->glClear(GL20::GDX_GL_COLOR_BUFFER_BIT);

		gl->glEnable(GL20::GDX_GL_TEXTURE_2D);
		shader->begin();
		shader->setUniformi("u_texture", 0);
		texture->bind();
		vbo->bind(shader);
		ibo->bind();
		gl->glDrawElements(GL20::GDX_GL_TRIANGLES, 3, GL20::GDX_GL_UNSIGNED_SHORT, 0);
		ibo->unbind();
		vbo->unbind(shader);
		shader->end();
	}
	
	void create()
	{
		std::string vertexShader = std::string() + "attribute vec4 a_position;    \n" + "attribute vec4 a_color;\n" + "attribute vec2 a_texCoords;\n"
			+ "varying vec4 v_color;" + "varying vec2 v_texCoords;" + "void main()                  \n"
			+ "{                            \n" + "   v_color = vec4(a_color.x, a_color.y, a_color.z, 1); \n"
			+ "   v_texCoords = a_texCoords; \n" + "   gl_Position =  a_position;  \n" + "}                            \n";
		std::string fragmentShader = std::string() + "#ifdef GL_ES\n" + "precision mediump float;\n" + "#endif\n" + "varying vec4 v_color;\n"
			+ "varying vec2 v_texCoords;\n" + "uniform sampler2D u_texture;\n" + "void main()                                  \n"
			+ "{                                            \n" + "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n"
			+ "}";

		shader = new ShaderProgram(vertexShader, fragmentShader);
		
		 VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 2, "a_position"),
			VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_texCoords"), 
			VertexAttribute(VertexAttributes::ColorPacked, 4, "a_color")};
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

	GDX_DEFINE_CREATOR(IndexBufferObjectShaderTest);
};

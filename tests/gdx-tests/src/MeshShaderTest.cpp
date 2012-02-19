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
#include "stdafx.h"
#include "MeshShaderTest.h"
#include "GdxRuntimeException.h"

bool MeshShaderTest::needsGL20 ()
{
	return true;
}

MeshShaderTest::MeshShaderTest()
	:m_axis(Vector3::Z), m_angle(0)
{
}

MeshShaderTest::~MeshShaderTest()
{
}

void MeshShaderTest::create() 
{
	std::string vertexShader = std::string("attribute vec4 a_position;    \n") + "attribute vec4 a_color;\n" + "attribute vec2 a_texCoords;\n"
			+ "uniform mat4 u_worldView;\n" + "varying vec4 v_color;" + "varying vec2 v_texCoords;"
			+ "void main()                  \n" + "{                            \n" + "   v_color = vec4(1, 1, 1, 1); \n"
			+ "   v_texCoords = a_texCoords; \n" + "   gl_Position =  u_worldView * a_position;  \n"
			+ "}                            \n";
	std::string fragmentShader = std::string("#ifdef GL_ES\n") + "precision mediump float;\n" + "#endif\n" + "varying vec4 v_color;\n"
			+ "varying vec2 v_texCoords;\n" + "uniform sampler2D u_texture;\n" + "void main()                                  \n"
			+ "{                                            \n" + "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n"
			+ "}";

	m_shader = new ShaderProgram(vertexShader, fragmentShader);

	if(!m_shader->isCompiled())
	{
		//Gdx.app->log("ShaderTest", m_shader->getLog());
		//System.exit(0);
		std::string shaderLog = m_shader->getLog();
	}

	VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 3, "a_position"), 
		VertexAttribute(VertexAttributes::Color, 4, "a_color"),
		VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_texCoords")};

		m_mesh = new Mesh(true, VertexAttributes(attributes, 3));

		float vertices[] = {-0.5f, -0.5f, 0, 1, 1, 1, 1, 0, 1, 0.5f, -0.5f, 0, 1, 1, 1, 1, 1, 1, 0.5f, 0.5f, 0, 1, 1, 1,
			1, 1, 0, -0.5f, 0.5f, 0, 1, 1, 1, 1, 0, 0};
		m_mesh->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
		short indices[] = {0, 1, 2, 2, 3, 0};
		m_mesh->setIndices(indices, sizeof(indices)/sizeof(indices[0]));

// Pixmap pixmap = new Pixmap(2, 1, Format.RGBA8888);
// pixmap.drawPixel(0, 0, 0xffff0000);
// pixmap.drawPixel(1, 0, 0xff00ff00);
// pixmap.drawPixel(0, 1, 0xff0000ff);
// pixmap.drawPixel(0, 0, 0xffff00ff);
// pixmap.drawPixel(1, 0, 0xffffff00);
// texture = Gdx.graphics.newUnmanagedTexture(pixmap, TextureFilter.Nearest, TextureFilter.Nearest, TextureWrap.ClampToEdge,
// TextureWrap.ClampToEdge);
// pixmap.dispose();
		m_texture = new Texture(Gdx.app->getFiles()->internalHandle("c:\\bobrgb888-32x32.png"));

		m_spriteBatch = new SpriteBatch();
		// font = Gdx.graphics.newFont("Arial", 12, FontStyle.Plain);
}


void MeshShaderTest::render() 
{
	m_angle += 1000/*TODO: Gdx.graphics->getDeltaTime()*/ * 45;
	m_matrix.setToRotation(m_axis, m_angle);

	//TODO Gdx.graphics->getGL20() must return GL20*
	//GL20* gl = Gdx.graphics->getGL20();
	GL20* gl = Gdx.gl20;
		gl->glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		gl->glClearColor(0.2f, 0.2f, 0.2f, 1);
		gl->glClear(GL20::GDX_GL_COLOR_BUFFER_BIT);
		gl->glEnable(GL20::GDX_GL_TEXTURE_2D);
		gl->glEnable(GL10::GDX_GL_BLEND);
		gl->glBlendFunc(GL10::GDX_GL_SRC_ALPHA, GL10::GDX_GL_ONE_MINUS_SRC_ALPHA);
		m_texture->bind();
		m_shader->begin();
		m_shader->setUniformMatrix(std::string("u_worldView"), m_matrix);
		m_shader->setUniformi("u_texture", 0);
		m_mesh->render(m_shader, GL10::GDX_GL_TRIANGLES);
		m_shader->end();

		m_spriteBatch->begin();
		// spriteBatch.drawText(font, "This is a test", 100, 100, Color.RED);
		m_spriteBatch->end();
}
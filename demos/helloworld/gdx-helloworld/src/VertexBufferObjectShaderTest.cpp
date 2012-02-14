#include "stdafx.h"
#include "VertexBufferObjectShaderTest.h"
#include "Color.h"

void VertexBufferObjectShaderTest::dispose()
{
	clean(m_texture);
	clean(m_vbo);
	clean(m_shader);
}

void VertexBufferObjectShaderTest::render()
{
	static short indices[] = {0,1,2};
	GL20* gl = Gdx.gl20;

	//TODO:
	//gl->glViewport(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
	//gl->glViewport(0, 0, 400, 300);
	gl->glClear(GL20::GDX_GL_COLOR_BUFFER_BIT);

	gl->glEnable(GL20::GDX_GL_TEXTURE_2D);
	m_shader->begin();
	m_shader->setUniformi( "u_texture", 0);
	m_texture->bind();
	m_vbo->bind(*m_shader);
	Gdx.gl->glDrawElements(GL20::GDX_GL_TRIANGLES, 3, GL20::GDX_GL_UNSIGNED_SHORT, &indices);
	m_vbo->unbind(*m_shader);
	m_shader->end();
}

void VertexBufferObjectShaderTest::create()
{
	std::string vertexShader = std::string("attribute vec4 a_position;    \n") + "attribute vec4 a_color;\n" + "attribute vec2 a_texCoords;\n"
		+ "varying vec4 v_color;" + "varying vec2 v_texCoords;" + "void main()                  \n"
		+ "{                            \n" + "   v_color = vec4(a_color.x, a_color.y, a_color.z, 1); \n"
		+ "   v_texCoords = a_texCoords; \n" + "   gl_Position =  a_position;  \n" + "}                            \n";
	std::string fragmentShader =  std::string("#ifdef GL_ES\n") + "precision mediump float;\n" + "#endif\n" + "varying vec4 v_color;\n"
		+ "varying vec2 v_texCoords;\n" + "uniform sampler2D u_texture;\n" + "void main()                                  \n"
		+ "{                                            \n" + "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n"
		+ "}";

	m_shader = new ShaderProgram(vertexShader, fragmentShader);
	//ShaderProgram::pedantic = false;

	VertexAttribute attributes[] = {VertexAttribute(VertexAttributes::Position, 2, "a_position"),
		VertexAttribute(VertexAttributes::TextureCoordinates, 2, "a_texCoords"), 
		VertexAttribute(VertexAttributes::ColorPacked, 4, "a_color")};
	m_vbo = new VertexBufferObject(true, VertexAttributes(attributes, sizeof(attributes)/sizeof(attributes[0])));

	float vertices[] = { -1, -1, 0, 0, Color::toFloatBits(1, 0, 0, 1), 0, 1, 0.5f, 1.0f,
		Color::toFloatBits(0, 1, 0, 1), 1, -1, 1, 0, Color::toFloatBits(0, 0, 1, 1)
	};

	m_vbo->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));

	m_texture = new Texture("c:\\badlogic.jpg");
}

void VertexBufferObjectShaderTest::resume()
{
	m_vbo->invalidate();
}


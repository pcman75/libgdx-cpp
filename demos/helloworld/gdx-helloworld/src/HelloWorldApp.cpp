#include "StdAfx.h"
#include "HelloWorldApp.h"
#include "Color.h"

HelloWorldApp::HelloWorldApp(void)
{
}


HelloWorldApp::~HelloWorldApp(void)
{
	dispose();
}

void HelloWorldApp::create ()
{
	VertexAttribute position(VertexAttributes::Position, 3, L"a_position");
	VertexAttribute color(VertexAttributes::ColorPacked, 4, L"a_color");
	VertexAttribute attributes[2] = {position, color};
	m_mesh = new Mesh(true, VertexAttributes(attributes, 2));
	float vertices[] = 
	{
		-0.5f, -0.5f, 0, Color::toFloatBits(255, 0, 0, 255),
		0.5f, -0.5f, 0, Color::toFloatBits(0, 255, 0, 255),
		0, 0.5f, 0, Color::toFloatBits(0, 0, 255, 255)
	};
	short indices[] = {0, 1, 2};
	m_mesh->setVertices(vertices, sizeof(vertices)/sizeof(vertices[0]));
	m_mesh->setIndices(indices, sizeof(indices)/sizeof(indices[0]));
}

void HelloWorldApp::resize (int width, int height){}

void HelloWorldApp::render ()
{
	Gdx.gl10->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
	m_mesh->render(GL10::GDX_GL_TRIANGLES, 0, 3);
}

void HelloWorldApp::pause (){}

void HelloWorldApp::resume (){}

void HelloWorldApp::dispose ()
{
	if(m_mesh)
	{
		delete m_mesh;
		m_mesh = NULL;
	}
}

#include "StdAfx.h"
#include "HelloWorldApp.h"
#include "Mesh.h"
#include "Gdx.h"

HelloWorldApp::HelloWorldApp(void)
{
	//TODO:
	create();
}


HelloWorldApp::~HelloWorldApp(void)
{
}

void HelloWorldApp::create ()
{
	VertexAttribute attrib(VertexAttributes::Position, 3, L"a_position");
	m_mesh = new Mesh(true, 3, 3, attrib);
	float vertices[] = {-0.5f, -0.5f, 0, 0.5f, -0.5f, 0, 0, 0.5f, 0};
	short indices[] = {0, 1, 2};
	m_mesh->setVertices(vertices, 0, sizeof(vertices)/sizeof(vertices[0]));
	m_mesh->setIndices(indices, 0, sizeof(indices)/sizeof(indices[0]));
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

#include "StdAfx.h"
#include "HelloWorldApp.h"


HelloWorldApp::HelloWorldApp(void)
{
}


HelloWorldApp::~HelloWorldApp(void)
{
}

void HelloWorldApp::create ()
{
}

void HelloWorldApp::resize (int width, int height){}

void HelloWorldApp::render ()
{
	// draw a triangle
    glBegin(GL_TRIANGLES);
        glNormal3f(0, 0, 1);
        glColor3f(1, 0, 0);
        glVertex3f(3, -2, 0);
        glColor3f(0, 1, 0);
        glVertex3f(0, 2, 0);
        glColor3f(0, 0, 1);
        glVertex3f(-3, -2, 0);
    glEnd();
}

void HelloWorldApp::pause (){}

void HelloWorldApp::resume (){}

void HelloWorldApp::dispose (){}

//
//  IOSGraphics.cpp
//  gdx-ios
//
//  Created by Tamas Jano on 09/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IOSGraphics.h"

IOSGraphics::IOSGraphics(bool useGL20): m_useGL20(useGL20)
{
    m_glVersion = GL_VERSION_0;
    m_frameStart = m_timer.systemNanoSeconds();
	m_lastFrameTime = m_frameStart;
	m_deltaTime = 0;
}

bool IOSGraphics::isGL11Available()
{
    return m_glVersion == GL_VERSION_11;
};

bool IOSGraphics::isGL20Available()
{
    return m_glVersion == GL_VERSION_20;
};

int IOSGraphics::getWidth()
{
    return m_width;
};

int IOSGraphics::getHeight()
{
    return m_height;
};

float IOSGraphics::getDeltaTime()
{
    return m_deltaTime;
};

int IOSGraphics::getFramesPerSecond()
{
    return m_fps;
};

Graphics::GraphicsType IOSGraphics::getType()
{
    return iOSGL;
};

float IOSGraphics::getPpiX()
{
    return -1;
};

float IOSGraphics::getPpiY()
{
    return -1;
};

float IOSGraphics::getPpcX()
{
    return -1;
};

float IOSGraphics::getPpcY()
{
    return -1;
};

float IOSGraphics::getDensity()
{
    return -1;
};

bool IOSGraphics::supportsDisplayModeChange()
{
    return false;
};


std::vector< Graphics::DisplayMode> IOSGraphics::getDisplayModes()
{
    return std::vector<Graphics::DisplayMode>();
};


Graphics::DisplayMode IOSGraphics::getDesktopDisplayMode()
{
    return DisplayMode(0, 0,0,0);
};

bool IOSGraphics::setDisplayMode (DisplayMode displayMode)
{
    return false;
};

bool IOSGraphics::setDisplayMode (int width, int height, bool fullscreen)
{
    return false;
};

void IOSGraphics::setTitle (std::string title)
{
    // TODO implement
};

void IOSGraphics::setVSync (bool vsync)
{
    // TODO implement
};

Graphics::BufferFormat IOSGraphics::getBufferFormat()
{
    return BufferFormat(0, 0, 0, 0, 0, 0, 0, false);
};

bool IOSGraphics::supportsExtension (std::string extension)
{
    return false;
};

GlVersion IOSGraphics::getGlVersion()
{
    return m_glVersion;
};

void IOSGraphics::setGlVersion(GlVersion version)
{
    m_glVersion = version;
};

void IOSGraphics::updateTimes() 
{
    // convert to seconds
	m_deltaTime = (m_timer.systemNanoSeconds() - m_lastFrameTime) * 1.0E-9f;
	m_lastFrameTime = m_timer.systemNanoSeconds();
    
	if(m_timer.systemNanoSeconds() - m_frameStart > 10E9) 
	{
		m_fps = m_frames;
		m_frames = 0;
		m_frameStart = m_timer.systemNanoSeconds();
	}
	m_frames++;
}

void IOSGraphics::updateSize(int width, int height) {
    m_width = width;
    m_height = height;
}

IOSGraphics::~IOSGraphics()
{
    
};
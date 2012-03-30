//
//  IOSGraphics.h
//  gdx-ios
//
//  Created by Tamas Jano on 06/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gdx_ios_IOSGraphics_h
#define gdx_ios_IOSGraphics_h

#include "Graphics.h"
#include "ApplicationListener.h"
#include "Gdx.h"
#include "IOSTimer.h"

class IOSGraphics : public Graphics
{
private:
	bool m_useGL20;
	bool created;
	bool exclusiveMode;
    
	int m_width;
	int m_height;
    
    GlVersion   m_glVersion;
	IOSTimer    m_timer;
	long long   m_frameStart;
	long long   m_lastFrameTime;
	float       m_deltaTime;
	int         m_fps;
	int         m_frames;
    
public:
    IOSGraphics(bool useGL20);
    virtual ~IOSGraphics();
    virtual bool isGL11Available();
	virtual bool isGL20Available();
	virtual int getWidth();
	virtual int getHeight();
	virtual float getDeltaTime();
	virtual int getFramesPerSecond ();
	virtual GraphicsType getType ();
	virtual float getPpiX ();
	virtual float getPpiY ();
	virtual float getPpcX ();
	virtual float getPpcY ();
	virtual float getDensity ();
	virtual bool supportsDisplayModeChange ();
	virtual std::vector<DisplayMode> getDisplayModes ();
	virtual DisplayMode getDesktopDisplayMode ();
	virtual bool setDisplayMode (DisplayMode displayMode);
	virtual bool setDisplayMode (int width, int height, bool fullscreen);
	virtual void setTitle (std::string title);
	virtual void setVSync (bool vsync);
	virtual BufferFormat getBufferFormat ();
	virtual bool supportsExtension (std::string extension);
    virtual GlVersion getGlVersion();
    virtual void setGlVersion(GlVersion version);

    virtual void updateTimes();
    virtual void updateTimes(float elapsedTime,  float timestamp);
};

#endif

//
//  IOSApplication.h
//  gdx-ios
//
//  Created by Tamas Jano on 09/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gdx_ios_IOSApplication_h
#define gdx_ios_IOSApplication_h

#include "Application.h"
#include "ApplicationListener.h"
#include "IOSGraphics.h"
#include "IOSApplicationConfiguration.h"

class IOSApplication : public Application {

public:
    IOSApplication(ApplicationListener& listener, bool useGL20);

    virtual ~IOSApplication();

	virtual Graphics* getGraphics ();
    
	virtual Audio* getAudio ();
    
	virtual Input* getInput ();
    
	virtual Files* getFiles ();
	
	virtual void log(const char* tag, const char* message);
    
	virtual void error (const char* tag, const char* message);
    
	virtual void debug (const char* tag, const char* message);

	virtual void setLogLevel (int logLevel);
    
	virtual ApplicationType getType ();

    virtual Timer* createTimer();
    
	virtual int getVersion ();
    
	virtual void exit ();

private:
    void initialize(IOSApplicationConfiguration& config);

	Graphics* m_pGraphics;
	Input* m_pInput;
	Files* m_pFiles;
	Audio* m_pAudio;
	int logLevel;
};

#endif

//
//  IOSApplication.cpp
//  gdx-ios
//
//  Created by Tamas Jano on 09/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "IOSApplication.h"
#include "IOSApplicationConfiguration.h"
#include "IOSGraphics.h"
#include "IOSTimer.h"
#include "IOSFiles.h"
#include "IOSInput.h"
#include "ApplicationDelegate.h"
#import <UIKit/UIKit.h>

IOSApplication::IOSApplication(ApplicationListener& listener, bool useGL20, int argc, char *argv[])
{
    m_listener = &listener;
    IOSApplicationConfiguration* config = new IOSApplicationConfiguration();
    initialize(*config);
    
    @autoreleasepool 
    {
        //refference ApplicationDelegate otherwise it's stripped by the linker
        //and UIApplicationMain will not find it
        [ApplicationDelegate alloc];
        UIApplicationMain(argc, argv, nil, @"ApplicationDelegate");
    }
};

IOSApplication::IOSApplication(ApplicationListener& listener, bool useGL20)
{
    m_listener = &listener;
    IOSApplicationConfiguration* config = new IOSApplicationConfiguration();
    initialize(*config);
};

void IOSApplication::initialize(IOSApplicationConfiguration& config) 
{
	logLevel = LOG_INFO;
	m_pGraphics = new IOSGraphics(false);
	m_pInput = new IOSInput();
	m_pFiles = new IOSFiles();
//	m_pAudio = new IOSAudio();
	
	Gdx.app = this;
	Gdx.graphics = m_pGraphics;
	Gdx.input = m_pInput;
	Gdx.audio = m_pAudio;
	Gdx.files = m_pFiles;
//	Gdx.threading = m_pThreading;
    
    
};

ApplicationListener* IOSApplication::getApplicationListener()
{
    return m_listener;
};


Graphics* IOSApplication::getGraphics()
{
    return m_pGraphics;
};

Audio* IOSApplication::getAudio()
{
    return m_pAudio;
};

Input* IOSApplication::getInput()
{
    return m_pInput;
};

Files* IOSApplication::getFiles()
{
    return m_pFiles;
};

Threading* IOSApplication::getThreading()
{
    return m_pThreading;
};
void IOSApplication::log(const char* tag, const char* message)
{
    printf("%s:\t%s\n", tag, message);
};

void IOSApplication::error (const char* tag, const char* message)
{
    
};

void IOSApplication::debug (const char* tag, const char* message)
{
    
};

void IOSApplication::setLogLevel (int logLevel)
{
    this->logLevel = logLevel;
};

IOSApplication::ApplicationType IOSApplication::getType()
{
    return iOS;
};

Timer* IOSApplication::createTimer()
{
    return new IOSTimer();
};

int IOSApplication::getVersion()
{
    return 0;
};

void IOSApplication::exit()
{
    exit();
};


IOSApplication::~IOSApplication()
{
    // cleanup
};


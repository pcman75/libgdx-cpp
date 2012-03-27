//
//  IOSApplication.cpp
//  gdx-ios
//
//  Created by Tamas Jano on 09/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IOSApplication.h"
#include "IOSApplicationConfiguration.h"
#include "IOSGraphics.h"

IOSApplication::IOSApplication(ApplicationListener& listener, bool useGL20)
{
    IOSApplicationConfiguration* config = new IOSApplicationConfiguration();
    initialize(*config);
};

void IOSApplication::initialize(IOSApplicationConfiguration& config) 
{
	logLevel = LOG_INFO;
	m_pGraphics = new IOSGraphics(true);
//	m_pInput = new IOSInput();
//	m_pFiles = new IOSFiles();
//	m_pAudio = new IOSAudio();
	
	Gdx.app = this;
	Gdx.graphics = m_pGraphics;
	Gdx.input = m_pInput;
	Gdx.audio = m_pAudio;
	Gdx.files = m_pFiles;
//	Gdx.threading = m_pThreading;
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

void IOSApplication::log(const char* tag, const char* message)
{
    
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
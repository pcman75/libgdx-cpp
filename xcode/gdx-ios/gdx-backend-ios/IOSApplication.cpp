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

IOSApplication::IOSApplication(ApplicationListener* listener, bool useGL20)
{
    IOSApplicationConfiguration config = IOSApplicationConfiguration();
    initialize(&config);
};

void IOSApplication::initialize(IOSApplicationConfiguration* config) 
{
};


IOSApplication::~IOSApplication()
{
    // cleanup
};
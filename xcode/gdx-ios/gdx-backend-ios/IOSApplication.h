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

    ApplicationListener* listener;
    IOSGraphics* graphics;
    
public:
    IOSApplication(ApplicationListener* listener, bool useGL20);
private:
    void initialize(ApplicationListener* listener, IOSApplicationConfiguration* config);
    void createGLView();
};

#endif

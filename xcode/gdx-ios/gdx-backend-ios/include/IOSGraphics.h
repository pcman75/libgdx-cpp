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

class IOSGraphics : public Graphics
{
    public:
    IOSGraphics(ApplicationListener& listener, bool useGL20);
};

#endif

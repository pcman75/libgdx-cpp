//
//  ApplicationDelegate.h
//  gdx-backend-ios
//
//  Created by Cosmin Manoliu on 13/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"
#import "IOSApplication.h"
#import "IOSAccelerometerHandler.h"

//@class RootViewController;

@interface ApplicationDelegate : UIResponder <UIApplicationDelegate>
{
    UIWindow*                   m_window;
    GLView*                     m_view;
    IOSApplication*             m_app;
    IOSAccelerometerHandler* m_accelHandler;
}

@property (strong, nonatomic) UIWindow *m_window;
//@property (nonatomic, retain) RootViewController *rootViewController;

-(ApplicationDelegate*) initWithApplication:(IOSApplication*)application;

@end

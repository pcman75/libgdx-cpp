//
//  AppDelegate.h
//  gdx-backend-ios
//
//  Created by Tamas Jano on 06/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"
#import "IOSApplication.h"

@class RootViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    UIWindow*                   m_window;
    GLView*                     m_view;
    IOSApplication*             m_app;
    
}

@property (strong, nonatomic) UIWindow *m_window;
//@property (nonatomic, retain) RootViewController *rootViewController;

-(AppDelegate*) initWithApplication:(IOSApplication*)application;

@end

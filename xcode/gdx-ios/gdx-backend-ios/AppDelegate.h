//
//  AppDelegate.h
//  gdx-backend-ios
//
//  Created by Tamas Jano on 06/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"

@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    UIWindow*                   m_window;
    GLView*                     m_view;
}

@property (strong, nonatomic) UIWindow *m_window;


@end

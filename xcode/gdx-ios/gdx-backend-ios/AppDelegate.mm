//
//  AppDelegate.m
//  gdx-backend-ios
//
//  Created by Tamas Jano on 06/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"
#import "../gdx-tests/AlphaTest.h"

@implementation AppDelegate

@synthesize m_window = _window;
//@synthesize rootViewController = _rootViewController;


-(AppDelegate*) initWithApplication:(IOSApplication*)application
{
    if (self = [super init]) 
    {
        m_app = application;
    };
    
    return self;
    
};

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{    
    // Instantiate the listener
    ApplicationListener *listener = new AlphaTest();
    // create the application
    m_app = new IOSApplication(*listener, true);
    
    [application setStatusBarHidden:YES];
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    
    self.m_window = [[UIWindow alloc] initWithFrame:screenBounds];
    
    m_view = [[GLView alloc] initWithFrame:screenBounds andListener:listener];

    [self.m_window addSubview:m_view];
    [self.m_window makeKeyAndVisible];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    [m_view startRenderLoop];

}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
    [m_view stopRenderLoop];

//    if (m_view) {
//        [m_view dealloc];
//    }

}

@end

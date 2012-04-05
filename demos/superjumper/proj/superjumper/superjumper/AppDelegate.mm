//
//  AppDelegate.m
//  superjumper
//
//  Created by Cosmin Manoliu on 4/5/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>

#import "AppDelegate.h"
#include "GlfwApplication.h"
#include "SuperJumper.h"

@implementation AppDelegate

@synthesize window = _window;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
}

- (IBAction)startGame:(id)sender
{
    SuperJumper superJumper;
    GlfwApplication(superJumper, "Super Jumper", 320, 480, true);
}

@end

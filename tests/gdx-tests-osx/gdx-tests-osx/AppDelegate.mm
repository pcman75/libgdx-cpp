//
//  AppDelegate.m
//  gdx-tests-osx
//
//  Created by Cosmin Manoliu on 3/21/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>

#import "AppDelegate.h"
#include "GdxTests.h"
#include "GlfwApplication.h"

@implementation AppDelegate

@synthesize window = _window;
@synthesize popUpButton = _popUpButton;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    for(GdxTests::TestsMapIterator it = GdxTests::tests.begin(); it != GdxTests::tests.end(); it++)
    {
        NSString* testName = [NSString stringWithUTF8String: it->first.c_str()];
        [_popUpButton addItemWithTitle: testName];
    }
}

- (IBAction)startTest:(id)sender 
{
    NSString* testName = [_popUpButton titleOfSelectedItem];
    NSLog([@"Starting test " stringByAppendingString: testName]);
    const char* szTestName = [testName UTF8String];
    
    
    GdxTest* test = GdxTests::newTest(szTestName);
    if(test)
    {
        GlfwApplication(*test, szTestName, 640, 480, test->needsGL20());
        delete test;
    }
}
@end

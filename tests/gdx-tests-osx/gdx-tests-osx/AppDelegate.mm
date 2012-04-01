//
//  AppDelegate.m
//  gdx-tests-osx
//
//  Created by Cosmin Manoliu on 3/21/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window = _window;
@synthesize popUpButton = _popUpButton;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [_popUpButton addItemWithTitle:@"Test"];
}

- (IBAction)startTest:(id)sender 
{
    NSLog(@"Startiung test");
}
@end

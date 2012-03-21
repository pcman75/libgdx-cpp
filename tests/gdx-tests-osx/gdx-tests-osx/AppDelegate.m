//
//  AppDelegate.m
//  gdx-tests-osx
//
//  Created by Cosmin Manoliu on 3/21/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize textField = _textField;
@synthesize slider = _slider;
@synthesize window = _window;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    
}

- (IBAction)takeFloatValueForVolumeFrom:(id)sender 
{
    NSString *senderName = nil;
    if (sender == self.textField) 
    {
        senderName = @"textField";
    }
    else 
    {
        senderName = @"slider";
    }
    float val = [sender floatValue];
    NSLog(@"%@ sent takeFloatValueForVolumeFrom: with value %1.2f", senderName, val);
    [_textField setFloatValue:(val)];
    [_slider setFloatValue:(val)];
}

- (IBAction)mute:(id)sender 
{
    NSLog(@"received a mute: message");
}
@end

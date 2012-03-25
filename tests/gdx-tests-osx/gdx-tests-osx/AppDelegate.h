//
//  AppDelegate.h
//  gdx-tests-osx
//
//  Created by Cosmin Manoliu on 3/21/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSPopUpButton *popUpButton;

- (IBAction)startTest:(id)sender;

@end

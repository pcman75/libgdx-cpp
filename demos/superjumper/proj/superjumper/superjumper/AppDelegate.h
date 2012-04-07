//
//  AppDelegate.h
//  superjumper
//
//  Created by Cosmin Manoliu on 4/5/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
- (IBAction)startGame:(id)sender;

@property (assign) IBOutlet NSWindow *window;

@end

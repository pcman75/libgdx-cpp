//
//  GLView.m
//  gdx-ios
//
//  Created by Tamas Jano on 06/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GLView.h"
#import <OpengLES/EAGLDrawable.h>
#import "mach/mach_time.h"
#import <OpenGLES/ES2/gl.h>

@implementation GLView

const bool forceES1 = false;

- (id)initWithFrame:(CGRect)frame
{
    if ((self = [super initWithFrame:frame])) {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque = YES;
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        context = [[EAGLContext alloc] initWithAPI:api];
        
        if (!context || forceES1) {
            api = kEAGLRenderingAPIOpenGLES1;
            context = [[EAGLContext alloc] initWithAPI:api];
        }
        
        if (!context || ![EAGLContext setCurrentContext:context]) {
//            [self release];   // compiler setting
            return nil;
        }
        
        // Context has been created...it should be good to go from here
                
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
        
        [self drawView:nil];
        
        timestamp = CACurrentMediaTime();
        
        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
    }
    return self;
}

- (void) drawView: (CADisplayLink*) displayLink
{
    if (displayLink != nil) {
        // TODO - need to do something with this to inject it into the Graphics instance
        float elapsedSeconds = displayLink.timestamp - timestamp;
        timestamp = displayLink.timestamp;
    }
    
    // delegating rendering to the application listener
    // appListener->render(elapsedSeconds);
    
    [context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) pause
{
    // appListener->pause();
}

- (void) resume
{
    // appListener->resume();
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
//    [context release];
    
//    [super dealloc];
}

@end

//
//  GLView.h
//  gdx-ios
//
//  Created by Tamas Jano on 06/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#include "ApplicationListener.h"
#include "IOSApplication.h"

@interface GLView : UIView {
@private
    EAGLContext*    context;
    float           timestamp;

    IOSApplication* app;
    ApplicationListener* listener;
    BOOL listenerInitialised;
    BOOL useDepthBuffer;

    CADisplayLink* displayLink;

    // The pixel dimensions of the CAEAGLLayer.
    GLint framebufferWidth;
    GLint framebufferHeight;

    GLuint defaultFramebuffer, colorRenderbuffer, depthRenderbuffer;
}

- (id)initWithFrame:(CGRect)frame andListener:(ApplicationListener*)listener;
//- (void) drawView: (CADisplayLink*)displayLink;
- (void) startRenderLoop;
- (void) stopRenderLoop;
- (void) drawFrame;
- (void) pause;
- (void) resume;
//- (void) setListener:(ApplicationListener*)listener;
- (void) setApplication:(IOSApplication*) application;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
@end

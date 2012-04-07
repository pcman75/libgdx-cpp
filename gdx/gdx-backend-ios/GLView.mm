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

@interface GLView (PrivateMethods)
- (void)createFramebuffer;
- (void)deleteFramebuffer;
@end

@implementation GLView

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame andListener:(ApplicationListener*)appListener
{
    if ((self = [super initWithFrame:frame])) {
        GlVersion glVersion = GL_VERSION_0;
        listener = appListener;
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        context = [[EAGLContext alloc] initWithAPI:api];
        
        if (!context || true) {
            NSLog(@"OpenGLES20 failed, trying GLES1");
            api = kEAGLRenderingAPIOpenGLES1;
            context = [[EAGLContext alloc] initWithAPI:api];
            glVersion = GL_VERSION_11;
        } else {
            glVersion = GL_VERSION_20;
        }
        
        if (!context || ![EAGLContext setCurrentContext:context]) {
//            [self release];   // compiler setting
            glVersion = GL_VERSION_0;
            return nil;
        }

        // updating gl version
        Gdx.graphics->setGlVersion(glVersion);

        // Context has been created...it should be good to go from here
        NSLog(@"Context created");
        
        useDepthBuffer = FALSE;
        
        listenerInitialised = FALSE;
        
        //default values for our OpenGL buffers
        defaultFramebuffer = 0;
        colorRenderbuffer = 0;
        depthRenderbuffer = 0;

    }
    return self;
}

- (void)createFramebuffer
{
    //this method assumes, that the context is valid and current, and that the default framebuffer has not been created yet!
    //this works, because as soon as we call glGenFramebuffers the value will be > 0
    assert(defaultFramebuffer == 0);
    
    NSLog(@"GLView: creating Framebuffer");
    
    // Create default framebuffer object and bind it
    glGenFramebuffers(1, &defaultFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
    
    // Create color render buffer
    glGenRenderbuffers(1, &colorRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    
    //get the storage from iOS so it can be displayed in the view
    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
    //get the frame's width and height
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
    
    //attach this color buffer to our framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
    
    //our lesson needs to know the size of the renderbuffer so it can work with the right aspect ratio
    if(listener != NULL)
    {
        listener->resize(framebufferWidth, framebufferHeight);
    }
    
    if(useDepthBuffer)
    {
        //create a depth renderbuffer
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        //create the storage for the buffer, optimized for depth values, same size as the colorRenderbuffer
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, framebufferWidth, framebufferHeight);
        //attach the depth buffer to our framebuffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
    }
    
    //check that our configuration of the framebuffer is valid
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
}

//deleting the framebuffer and all the buffers it contains
- (void)deleteFramebuffer
{
    //we need a valid and current context to access any OpenGL methods
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        //if the default framebuffer has been set, delete it.
        if (defaultFramebuffer) {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        //same for the renderbuffers, if they are set, delete them
        if (colorRenderbuffer) {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
        
        if (depthRenderbuffer) {
            glDeleteRenderbuffers(1, &depthRenderbuffer);
            depthRenderbuffer = 0;
        }
    }
}

- (void)startRenderLoop
{
    //check whether the loop is already running
    if(displayLink == nil)
    {
        //the display link specifies what to do when the screen has to be redrawn,
        //here we use the selector (method) drawFrame
        displayLink = [self.window.screen displayLinkWithTarget:self selector:@selector(drawFrame)];
        
        //by adding the display link to the run loop our draw method will be called 60 times per second
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

        //setting timer
        timestamp = CACurrentMediaTime();

        NSLog(@"Starting Render Loop");
    }
    [self resume];
}

//we have to be able to stop the render loop
- (void)stopRenderLoop
{
    if (displayLink != nil) {
        //if the display link is present, we invalidate it (so the loop stops)
        [displayLink invalidate];
        displayLink = nil;
        NSLog(@"Stopping Render Loop");
        [self pause];
    }
}


- (void)drawFrame
{
    //we need a context for rendering
    if (context != nil)
    {
        //make it the current context for rendering
        [EAGLContext setCurrentContext:context];
        
        //if our framebuffers have not been created yet, do that now!
        if (!defaultFramebuffer)
            [self createFramebuffer];
        
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        //we need a listener to be able to render something
        if(listener != nil)
        {
            //check whether we have to initialize the listener
            if(listenerInitialised == FALSE)
            {
                listener->create();
                listenerInitialised = TRUE;
            }
            
            //perform the actual drawing!
            listener->render();
        }
        
        float elapsedSeconds = displayLink.timestamp - timestamp;
        timestamp = displayLink.timestamp;
//        NSLog(@"elapsedSeconds=%f  timestamp=%f", elapsedSeconds, timestamp);
        // update deltaTime
        ((IOSGraphics*)Gdx.graphics)->updateTimes(elapsedSeconds, timestamp);

        //finally, get the color buffer we rendered to, and pass it to iOS
        //so it can display our awesome results!
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    else
        NSLog(@"Context not set!");
}


- (void) pause
{
    listener->pause();
}

- (void) resume
{
//    listener->resume();
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
//    [context release];
    
//    [super dealloc];
}

- (void) setApplication:(IOSApplication*)application
{
    app = application;
//    listener = app->get
    listenerInitialised = FALSE;
}
@end

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

@interface GLView : UIView {
@private
    EAGLContext*    context;
    float           timestamp;
}

- (id)initWithFrame:(CGRect)frame;
- (void) drawView: (CADisplayLink*)displayLink;
- (void) pause;
- (void) resume;

@end

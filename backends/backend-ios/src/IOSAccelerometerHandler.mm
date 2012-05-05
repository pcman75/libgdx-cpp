//
//  IOSAccelerometerHandler.m
//  backend-ios
//
//  Created by Cosmin Manoliu on 5/5/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#import "IOSAccelerometerHandler.h"
#import "UIKit/UIAccelerometer.h"
#import "Gdx.h"
#include "IOSInput.h"

@implementation IOSAccelerometerHandler

- (void)configureAccelerometer
{
    UIAccelerometer*  theAccelerometer = [UIAccelerometer sharedAccelerometer];
    theAccelerometer.updateInterval = 1 / 50;
    
    theAccelerometer.delegate = self;
    // Delegate events begin immediately.
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration 
{
    //TODO: which is the accelelerometer range?
    IOSInput* input = (IOSInput*)Gdx.input;
    input->m_accelX = - acceleration.x * 10;
    input->m_accelY = - acceleration.y * 10;
    input->m_accelZ = - acceleration.z * 10;
}

@end

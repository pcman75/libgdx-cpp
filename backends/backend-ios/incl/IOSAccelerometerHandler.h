//
//  IOSAccelerometerHandler.h
//  backend-ios
//
//  Created by Cosmin Manoliu on 5/5/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "UIKit/UIAccelerometer.h"

@interface IOSAccelerometerHandler : NSObject<UIAccelerometerDelegate>

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration;
- (void)configureAccelerometer;

@end

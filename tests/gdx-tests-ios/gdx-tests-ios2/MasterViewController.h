//
//  MasterViewController.h
//  gdx-tests-ios2
//
//  Created by Cosmin Manoliu on 5/16/12.
//  Copyright (c) 2012 Home. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DetailViewController;

@interface MasterViewController : UITableViewController

@property (strong, nonatomic) DetailViewController *detailViewController;

@end

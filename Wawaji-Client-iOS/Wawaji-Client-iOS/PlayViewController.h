//
//  PlayViewController.h
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/10/24.
//  Copyright © 2017 Agora. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "WawajiInfo.h"

@interface PlayViewController : UIViewController

@property (copy, nonatomic) NSString *account;
@property (strong, nonatomic) WawajiInfo *wawaji;

@end

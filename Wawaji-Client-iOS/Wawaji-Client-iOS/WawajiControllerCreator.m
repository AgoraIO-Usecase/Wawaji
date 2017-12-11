//
//  WawajiControllerCreator.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/12/2.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "WawajiControllerCreator.h"
#import "LeidiWawajiController.h"
#import "LeyaoyaoWawajiController.h"
#import "ZinianWawajiController.h"

@implementation WawajiControllerCreator

+ (id<WawajiController>)getWawajiController:(WawajiManufacturer)manufacturer {
    id<WawajiController> wawajiController;
    
    switch (manufacturer) {
        case WawajiManufacturer_LeiDi:
            wawajiController = [[LeidiWawajiController alloc] init];
            break;
            
        case WawajiManufacturer_LeYaoYao:
            wawajiController = [[LeyaoyaoWawajiController alloc] init];
            break;
            
        case WawajiManufacturer_ZiNian:
            wawajiController = [[ZinianWawajiController alloc] init];
            break;
            
        default:
            wawajiController = nil;
            break;
    }
    
    return wawajiController;
}

@end

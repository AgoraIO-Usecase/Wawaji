//
//  WawajiControllerCreator.h
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/12/2.
//  Copyright © 2017 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WawajiController.h"

typedef NS_ENUM(NSInteger, WawajiManufacturer) {
    WawajiManufacturer_LeiDi,
    WawajiManufacturer_LeYaoYao,
    WawajiManufacturer_ZiNian,
};

@interface WawajiControllerCreator : NSObject

+ (id<WawajiController>)getWawajiController:(WawajiManufacturer)manufacturer;

@end

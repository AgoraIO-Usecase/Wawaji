//
//  KeyCenter.h
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/11/22.
//  Copyright © 2017 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KeyCenter : NSObject

+ (NSString *)appId;

+ (NSString *)generateSignalToken:(NSString*)account expiredTime:(unsigned)expiredTimeIntervalSinceNow;

+ (NSString *)generateMediaKey:(NSString*)channel uid:(uint32_t)uid expiredTime:(uint32_t)expiredTime;

@end

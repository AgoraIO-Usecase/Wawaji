//
//  KeyCenter.h
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/10/16.
//  Copyright © 2017 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface KeyCenter : NSObject

+ (NSString *)mediaAppId;
+ (NSString *)signalAppId;

+ (NSString *)generateSignalToken:(NSString*)account expiredTime:(unsigned)expiredTimeIntervalSinceNow;

@end

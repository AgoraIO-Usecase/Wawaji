//
//  KeyCenter.mm
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/10/24.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "KeyCenter.h"
#import <CommonCrypto/CommonDigest.h>

#include "DynamicKey4.h"

static NSString * const kMediaAppID = <#Your App ID#>;

static NSString * const kSignalAppID = <#Your App ID#>;
static NSString * const kSignalAppCertificate = <#Your App Certificate#>;

@implementation KeyCenter

+ (NSString *)mediaAppId {
    return kMediaAppID;
}

+ (NSString *)signalAppId {
    return kSignalAppID;
}

+ (NSString*)md5:(NSString*)string
{
    // Create pointer to the string as UTF8
    const char *ptr = [string UTF8String];
    
    // Create byte array of unsigned chars
    unsigned char md5Buffer[CC_MD5_DIGEST_LENGTH];
    
    // Create 16 byte MD5 hash value, store in buffer
    CC_MD5(ptr, (CC_LONG)strlen(ptr), md5Buffer);
    
    // Convert MD5 value in the buffer to NSString of hex values
    NSMutableString *output = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    for(int i = 0; i < CC_MD5_DIGEST_LENGTH; i++)
        [output appendFormat:@"%02x",md5Buffer[i]];
    
    return output;
}

+ (NSString *)generateSignalToken:(NSString*)account expiredTime:(unsigned)expiredTimeIntervalSinceNow
{
    // Token = 1:appID:expiredTime:sign
    // Token = 1:appID:expiredTime:md5(account + vendorID + certificate + expiredTime)
    
    unsigned expiredTime = (unsigned)[[NSDate date] timeIntervalSince1970] + expiredTimeIntervalSinceNow;
    NSString * sign = [self md5:[NSString stringWithFormat:@"%@%@%@%d", account, kSignalAppID, kSignalAppCertificate, expiredTime]];
    return [NSString stringWithFormat:@"1:%@:%d:%@", kSignalAppID, expiredTime, sign];
}

@end

//
//  KeyCenter.mm
//  SignalingTestDemo
//
//  Created by suleyu on 2017/10/25.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "KeyCenter.h"
#import <CommonCrypto/CommonDigest.h>

#include "DynamicKey4.h"

static NSString * const kAppID = <#Your App ID#>;
static NSString * const kAppCertificate = <#Your App Certificate#>;

@implementation KeyCenter

+ (NSString *)appId {
    return kAppID;
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
    NSString * sign = [self md5:[NSString stringWithFormat:@"%@%@%@%d", account, kAppID, kAppCertificate, expiredTime]];
    return [NSString stringWithFormat:@"1:%@:%d:%@", kAppID, expiredTime, sign];
}

+ (NSString *)generateMediaKey:(NSString*)channel uid:(uint32_t)uid expiredTime:(uint32_t)expiredTime
{
    std::string x = agora::tools::DynamicKey4::generateMediaChannelKey(kAppID.UTF8String,
                                                                       kAppCertificate.UTF8String,
                                                                       channel.UTF8String,
                                                                       (uint32_t)time(NULL),
                                                                       (rand()%256 << 24) + (rand()%256 << 16) + (rand()%256 << 8) + (rand()%256),
                                                                       0,
                                                                       expiredTime).c_str();
    return [NSString stringWithCString:x.c_str() encoding:NSUTF8StringEncoding] ;
}

@end

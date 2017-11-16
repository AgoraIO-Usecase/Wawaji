//
//  NSObject+JSONString.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/10/24.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "NSObject+JSONString.h"

@implementation NSObject (JSONString)

- (NSString *)JSONString
{
    NSData *data = [NSJSONSerialization dataWithJSONObject:self options:NSJSONWritingPrettyPrinted error:nil];
    return [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
}

@end

//
//  WawajiController.h
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/12/2.
//  Copyright © 2017 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol WawajiController <NSObject>

- (void)initialize;

- (void)insertCion;

- (BOOL)startMoveUp;

- (BOOL)stopMoveUp;

- (BOOL)startMoveDown;

- (BOOL)stopMoveDown;

- (BOOL)startMoveLeft;

- (BOOL)stopMoveLeft;

- (BOOL)startMoveRight;

- (BOOL)stopMoveRight;

- (BOOL)fetch;

@optional
@property (copy, nonatomic) void (^fetchResultBlock)(BOOL result);

@end

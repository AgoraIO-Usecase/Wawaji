//
//  LeidiWawajiController.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/12/11.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "LeidiWawajiController.h"
#import "SocketRocket.h"

static NSString * const kWebSocketUrl = <#Leidi Server Address#>;
static const int kRoomId = <#Leidi Room ID#>;

@interface LeidiWawajiController () <SRWebSocketDelegate>

@property (strong, nonatomic) SRWebSocket *webSocket;
@property (assign, nonatomic) int roomId;

@end

@implementation LeidiWawajiController
@synthesize fetchResultBlock = _fetchResultBlock;

- (void)dealloc {
    [self.webSocket close];
    self.webSocket.delegate = nil;
    self.webSocket = nil;
}

- (void)initialize {
    self.roomId = kRoomId;
    [self connectWebSocket];
}

- (void)insertCion {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/start", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
}

- (BOOL)startMoveUp {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/move/back", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"data" : @{@"time" : @10000}, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)stopMoveUp {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/stop", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)startMoveDown {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/move/front", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"data" : @{@"time" : @10000}, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)stopMoveDown {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/stop", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)startMoveLeft {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/move/left", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"data" : @{@"time" : @10000}, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)stopMoveLeft {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/stop", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)startMoveRight {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/move/right", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"data" : @{@"time" : @10000}, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)stopMoveRight {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/stop", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)fetch {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/catch", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

// MARK: - WebSocket

- (void)connectWebSocket {
    [self.webSocket close];
    self.webSocket.delegate = nil;
    self.webSocket = nil;
    
    SRWebSocket *newWebSocket = [[SRWebSocket alloc] initWithURL:[NSURL URLWithString:kWebSocketUrl]];
    newWebSocket.delegate = self;
    [newWebSocket open];
}

- (void)sendWebSocketMessage:(NSDictionary *)message {
    NSData *data = [NSJSONSerialization dataWithJSONObject:message options:NSJSONWritingPrettyPrinted error:nil];
    NSString *string = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSLog(@"sendWebSocketMessage: %@", string);
    [self.webSocket send:string];
}

- (void)sendEnterCommand {
    NSString *uri = [NSString stringWithFormat:@"/rooms/%d/enter", self.roomId];
    NSInteger timeInterval = [NSDate date].timeIntervalSinceReferenceDate * 1000;
    NSDictionary *msgDic = @{@"uri" : uri, @"data" : @{@"token" : @"no_token"}, @"type" : @"post", @"id" : @(timeInterval)};
    [self sendWebSocketMessage:msgDic];
}

- (void)webSocketDidOpen:(SRWebSocket *)newWebSocket {
    NSLog(@"webSocketDidOpen");
    self.webSocket = newWebSocket;
    [self sendEnterCommand];
}

- (void)webSocket:(SRWebSocket *)webSocket didFailWithError:(NSError *)error {
    NSLog(@"webSocket:didFailWithError: %@", error);
    [self connectWebSocket];
}

- (void)webSocket:(SRWebSocket *)webSocket didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean {
    NSLog(@"webSocket:didCloseWithCode: %d, reason: %@", (int)code, reason);
    [self connectWebSocket];
}

- (void)webSocket:(SRWebSocket *)webSocket didReceiveMessage:(id)message {
    NSLog(@"webSocket:didReceiveMessage: %@", message);
    
    NSData *data = [message dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
    if (dic[@"id"] == nil && [dic[@"type"] isEqualToString:@"message"]) {
        NSNumber *result = dic[@"data"][@"result"];
        if (result) {
            BOOL success = [result intValue] == 1;
            if (self.fetchResultBlock) {
                self.fetchResultBlock(success);
            }
        }
    }
}

@end

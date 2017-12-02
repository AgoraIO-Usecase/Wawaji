//
//  ZinianWawajiController.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/12/2.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "ZinianWawajiController.h"
#import "SocketRocket.h"

static NSString * const kWebSocketUrl = @"Your Wawaji Controlling WebSocket Url";

@interface ZinianWawajiController () <SRWebSocketDelegate>
{
    SRWebSocket *webSocket;
}
@end

@implementation ZinianWawajiController

- (void)dealloc {
    [webSocket close];
    webSocket.delegate = nil;
    webSocket = nil;
}

- (void)initialize {
    [self connectWebSocket];
}

- (void)insertCion {
    NSDictionary *msgDic = @{@"type" : @"Insert", @"data" : @"", @"extra" : @(123456)};
    [self sendWebSocketMessage:msgDic];
}

- (BOOL)startMoveUp {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"u"};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)stopMoveUp {
    return NO;
}

- (BOOL)startMoveDown {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"d"};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)stopMoveDown {
    return NO;
}

- (BOOL)startMoveLeft {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"l"};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)stopMoveLeft {
    return NO;
}

- (BOOL)startMoveRight {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"r"};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

- (BOOL)stopMoveRight {
    return NO;
}

- (BOOL)fetch {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"b"};
    [self sendWebSocketMessage:msgDic];
    return YES;
}

// MARK: - WebSocket

- (void)connectWebSocket {
    [webSocket close];
    webSocket.delegate = nil;
    webSocket = nil;
    
    SRWebSocket *newWebSocket = [[SRWebSocket alloc] initWithURL:[NSURL URLWithString:kWebSocketUrl]];
    newWebSocket.delegate = self;
    [newWebSocket open];
}

- (void)sendWebSocketMessage:(NSDictionary *)message {
    NSData *data = [NSJSONSerialization dataWithJSONObject:message options:NSJSONWritingPrettyPrinted error:nil];
    NSString *string = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSLog(@"sendWebSocketMessage: %@", string);
    [webSocket send:string];
}

- (void)webSocketDidOpen:(SRWebSocket *)newWebSocket {
    webSocket = newWebSocket;
}

- (void)webSocket:(SRWebSocket *)webSocket didFailWithError:(NSError *)error {
    [self connectWebSocket];
}

- (void)webSocket:(SRWebSocket *)webSocket didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean {
    [self connectWebSocket];
}

- (void)webSocket:(SRWebSocket *)webSocket didReceiveMessage:(id)message {
}

@end

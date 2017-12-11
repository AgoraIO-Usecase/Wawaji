//
//  LeyaoyaoWawajiController.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/12/2.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "LeyaoyaoWawajiController.h"
#import "SocketRocket.h"

static NSString * const kLeyaoyaoServer = @"https://live.leyaoyao.com";
static NSString * const kLeyaoyaoAppID = <#Your App ID from Leyaoyao#>;

static NSString * const kBinding = @"UserId";
static const int kRoomId = <#Leyaoyao Room ID#>; // you can get all available rooms by getRooms method

@interface LeyaoyaoWawajiController () <SRWebSocketDelegate>

@property (strong, nonatomic) SRWebSocket *webSocket;

@end

@implementation LeyaoyaoWawajiController
@synthesize fetchResultBlock = _fetchResultBlock;

- (void)dealloc {
    [self.webSocket close];
    self.webSocket.delegate = nil;
    self.webSocket = nil;
}

- (void)initialize {
//    [self getRooms];
    [self createUser];
}

- (void)insertCion {
    [self getWebSocketUrl:kRoomId];
}

- (BOOL)startMoveUp {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"u"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

- (BOOL)stopMoveUp {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"W"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

- (BOOL)startMoveDown {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"d"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

- (BOOL)stopMoveDown {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"S"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

- (BOOL)startMoveLeft {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"l"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

- (BOOL)stopMoveLeft {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"A"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

- (BOOL)startMoveRight {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"r"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

- (BOOL)stopMoveRight {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"D"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

- (BOOL)fetch {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @{@"direction" : @"b"}, @"extra" : @(extra)};
    return [self sendWebSocketMessage:msgDic];
}

// MARK: - HTTP Connection

- (void)getRooms {
    NSString *urlString = [NSString stringWithFormat:@"%@/api/rooms?appId=%@", kLeyaoyaoServer, kLeyaoyaoAppID];
    NSURL *url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData timeoutInterval:10];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPMethod:@"GET"];
    
    NSURLSessionDataTask *dataTask = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            NSLog(@"get rooms error : %@", error);
            return;
        }
        
        if (response == nil) {
            NSLog(@"get rooms response is nil");
            return;
        }
        
        NSInteger statusCode = ((NSHTTPURLResponse *)response).statusCode;
        if (statusCode != 200) {
            NSLog(@"get rooms response code : %d", (int)statusCode);
            return;
        }
        
        NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@"get rooms return : %@", jsonString);
        
        NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
        int result = [dic[@"result"] intValue];
        if (result == 0) {
            NSDictionary *data = dic[@"data"];
            NSArray *rooms = data[@"rooms"];
            for (NSDictionary *room in rooms) {
                int roomId = [room[@"id"] intValue];
                NSLog(@"room id : %d", roomId);
            }
        }
    }];
    [dataTask resume];
}

- (void)createUser {
    NSDictionary *params = @{@"appId" : kLeyaoyaoAppID, @"binding" : kBinding};
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:params options:NSJSONWritingPrettyPrinted error:nil];
    
    NSString *urlString = [NSString stringWithFormat:@"%@/api/users", kLeyaoyaoServer];
    NSURL *url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData timeoutInterval:10];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPMethod:@"POST"];
    [request setHTTPBody:jsonData];
    
    NSURLSessionDataTask *dataTask = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            NSLog(@"create user error : %@", error);
            return;
        }
        
        if (response == nil) {
            NSLog(@"create user response is nil");
            return;
        }
        
        NSInteger statusCode = ((NSHTTPURLResponse *)response).statusCode;
        if (statusCode != 200) {
            NSLog(@"create user response code : %d", (int)statusCode);
            return;
        }
        
        NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@"create user return : %@", jsonString);
        
        NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
        int result = [dic[@"result"] intValue];
        if (result == 0) {
            NSDictionary *data = dic[@"data"];
            NSDictionary *user = data[@"user"];
            int account = [user[@"account"] intValue];
            NSLog(@"account : %d", account);
            
            // FIXME: auto charge, just for demo
            if (account < 10000) {
                [self charge:10000];
            }
        }
    }];
    [dataTask resume];
}

- (void)charge:(int)account {
    NSDictionary *params = @{@"appId" : kLeyaoyaoAppID, @"binding" : kBinding, @"amount" : @(account)};
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:params options:NSJSONWritingPrettyPrinted error:nil];
    
    NSString *urlString = [NSString stringWithFormat:@"%@/api/charge", kLeyaoyaoServer];
    NSURL *url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData timeoutInterval:10];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPMethod:@"POST"];
    [request setHTTPBody:jsonData];

    NSURLSessionDataTask *dataTask = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            NSLog(@"charge error : %@", error);
            return;
        }
        
        if (response == nil) {
            NSLog(@"charge response is nil");
            return;
        }
        
        NSInteger statusCode = ((NSHTTPURLResponse *)response).statusCode;
        if (statusCode != 200) {
            NSLog(@"charge response code : %d", (int)statusCode);
            return;
        }
        
        NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@"charge return : %@", jsonString);
        
        NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
        int result = [dic[@"result"] intValue];
        if (result == 0) {
            NSLog(@"charge success");
        }
        else {
            NSLog(@"charge failed");
        }
    }];
    [dataTask resume];
}

- (void)getWebSocketUrl:(int)room {
    NSString *urlString = [NSString stringWithFormat:@"%@/api/websocket_url?appId=%@&binding=%@&roomId=%d", kLeyaoyaoServer, kLeyaoyaoAppID, kBinding, room];
    NSURL *url = [NSURL URLWithString:urlString];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url cachePolicy:NSURLRequestReloadIgnoringLocalAndRemoteCacheData timeoutInterval:10];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPMethod:@"GET"];
    
    NSURLSessionDataTask *dataTask = [[NSURLSession sharedSession] dataTaskWithRequest:request completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            NSLog(@"get websocket url error : %@", error);
            return;
        }
        
        if (response == nil) {
            NSLog(@"get websocket url response is nil");
            return;
        }
        
        NSInteger statusCode = ((NSHTTPURLResponse *)response).statusCode;
        if (statusCode != 200) {
            NSLog(@"get websocket url response code : %d", (int)statusCode);
            return;
        }
        
        NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@"get websocket url return : %@", jsonString);
        
        NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
        int result = [dic[@"result"] intValue];
        if (result == 0) {
            NSDictionary *data = dic[@"data"];
            NSString *webSocketUrl = data[@"wsUrl"];
            NSLog(@"get websocket url : %@", webSocketUrl);
            
            [self connectWebSocket:webSocketUrl];
        }
    }];
    [dataTask resume];
}

// MARK: - WebSocket

- (void)connectWebSocket:(NSString *)urlString {
    [self.webSocket close];
    self.webSocket.delegate = nil;
    self.webSocket = nil;
    
    SRWebSocket *newWebSocket = [[SRWebSocket alloc] initWithURL:[NSURL URLWithString:urlString]];
    newWebSocket.delegate = self;
    [newWebSocket open];
}

- (BOOL)sendWebSocketMessage:(NSDictionary *)message {
    if (self.webSocket == nil) {
        return NO;
    }

    NSData *data = [NSJSONSerialization dataWithJSONObject:message options:NSJSONWritingPrettyPrinted error:nil];
    NSString *string = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSLog(@"sendWebSocketMessage: %@", string);
    [self.webSocket send:string];
    return YES;
}

- (void)sendInsertCommand {
    NSInteger extra = [NSDate date].timeIntervalSince1970;
    NSDictionary *msgDic = @{@"type" : @"Insert", @"data" : [NSNull null], @"extra" : @(extra)};
    [self sendWebSocketMessage:msgDic];
}

- (void)webSocketDidOpen:(SRWebSocket *)newWebSocket {
    NSLog(@"webSocketDidOpen");
    self.webSocket = newWebSocket;
    [self sendInsertCommand];
}

- (void)webSocket:(SRWebSocket *)webSocket didFailWithError:(NSError *)error {
    NSLog(@"webSocket:didFailWithError: %@", error);
    self.webSocket = nil;
}

- (void)webSocket:(SRWebSocket *)webSocket didCloseWithCode:(NSInteger)code reason:(NSString *)reason wasClean:(BOOL)wasClean {
    NSLog(@"webSocket:didCloseWithCode: %d, reason: %@", (int)code, reason);
    self.webSocket = nil;
}

- (void)webSocket:(SRWebSocket *)webSocket didReceiveMessage:(id)message {
    NSLog(@"webSocket:didReceiveMessage: %@", message);
    
    NSData *data = [message dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
    NSString *type = dic[@"type"];
    if ([type isEqualToString:@"Result"]) {
        [webSocket close];
        webSocket.delegate = nil;
        self.webSocket = nil;
        
        BOOL result = [dic[@"data"] boolValue];
        if (self.fetchResultBlock) {
            self.fetchResultBlock(result);
        }
    }
}

@end

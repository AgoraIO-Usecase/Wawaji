//
//  PlayViewController.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/10/24.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "PlayViewController.h"
#import "KeyCenter.h"
#import "SocketRocket.h"
#import "NSObject+JSONString.h"
#import "AlertUtil.h"
#import <AgoraSignalKit/AgoraSignalKit.h>
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

static NSString * const kServerUrlString = <#Your Wawaji Controlling Protocol Server#>;
static NSString * const kRemoteSignalAccount = @"meixi";

@interface PlayViewController () <AgoraRtcEngineDelegate, SRWebSocketDelegate>
{
    AgoraRtcEngineKit *mediaEngine;
    AgoraAPI *signalEngine;
    SRWebSocket *webSocket;
}

@property (assign, nonatomic) uint32_t signalUid;
@property (weak, nonatomic) IBOutlet UIView *videoView;
@property (weak, nonatomic) IBOutlet UIView *controlView;

@end

@implementation PlayViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.navigationItem.title = self.channel;
    
    [self loadMediaEngine];
    [self loadSignalEngine];
    
    if (self.player) {
        [self connectWebSocket];
    }
    else {
        [self.controlView removeFromSuperview];
    }
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [UIApplication sharedApplication].idleTimerDisabled = NO;
    [mediaEngine leaveChannel:nil];
    mediaEngine = nil;
    
    [signalEngine logout];
    signalEngine = nil;
    
    [webSocket close];
    webSocket.delegate = nil;
    webSocket = nil;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)leave:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)switchCamera:(id)sender {
    NSDictionary *msgDic = @{@"uid" : [NSString stringWithFormat:@"%d", self.signalUid], @"opeType" : @(1), @"opeAttr" : @"iOS"};
    NSString *msg = [msgDic JSONString];
    [signalEngine messageInstantSend:kRemoteSignalAccount uid:0 msg:msg msgID:nil];
}

- (IBAction)cion:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"Insert", @"data" : @"", @"extra" : @(123456)};
    [webSocket send:[msgDic JSONString]];
}

- (IBAction)up:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"u"};
    [webSocket send:[msgDic JSONString]];
}

- (IBAction)down:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"d"};
    [webSocket send:[msgDic JSONString]];
}

- (IBAction)left:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"l"};
    [webSocket send:[msgDic JSONString]];
}

- (IBAction)right:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"r"};
    [webSocket send:[msgDic JSONString]];
}

- (IBAction)grab:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"Control", @"data" : @"b"};
    [webSocket send:[msgDic JSONString]];
}

// MARK: - Media Engine

- (void)loadMediaEngine {
    mediaEngine = [AgoraRtcEngineKit sharedEngineWithAppId:[KeyCenter mediaAppId] delegate:self];
    [mediaEngine setChannelProfile:AgoraRtc_ChannelProfile_LiveBroadcasting];
    [mediaEngine setClientRole:AgoraRtc_ClientRole_Broadcaster withKey:nil];
    [mediaEngine enableVideo];
    [mediaEngine enableLocalVideo:NO];
    [mediaEngine muteLocalAudioStream:YES];
    [mediaEngine setParameters:@"{\"che.audio.external_capture\": true}"];
    int result = [mediaEngine joinChannelByKey:nil channelName:self.channel info:nil uid:0 joinSuccess:nil];
    if (result == 0) {
        [UIApplication sharedApplication].idleTimerDisabled = YES;
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didOccurWarning:(AgoraRtcWarningCode)warningCode {
    NSLog(@"rtcEngine:didOccurWarning: %ld", (long)warningCode);
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didOccurError:(AgoraRtcErrorCode)errorCode {
    NSLog(@"rtcEngine:didOccurError: %ld", (long)errorCode);
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didJoinChannel:(NSString*)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed {
    NSLog(@"rtcEngine:didJoinChannel: %@", channel);
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed {
    NSLog(@"rtcEngine:didJoinedOfUid: %ld", (long)uid);
    AgoraRtcVideoCanvas *videoCanvas = [[AgoraRtcVideoCanvas alloc] init];
    videoCanvas.uid = uid;
    videoCanvas.view = self.videoView;
    videoCanvas.renderMode = AgoraRtc_Render_Hidden;
    [mediaEngine setupRemoteVideo:videoCanvas];
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didOfflineOfUid:(NSUInteger)uid reason:(AgoraRtcUserOfflineReason)reason {
    NSLog(@"rtcEngine:didOfflineOfUid: %ld", (long)uid);
    [AlertUtil showAlert:@"Remote device offline" completion:^{
        [self dismissViewControllerAnimated:NO completion:nil];
    }];
}

// MARK: - Signal Engine

- (void)loadSignalEngine {
    __weak typeof(self) weakSelf = self;
    
    signalEngine = [AgoraAPI getInstanceWithoutMedia:[KeyCenter signalAppId]];
    signalEngine.onLog = ^(NSString *txt){
        NSLog(@"%@", txt);
    };
    
    signalEngine.onLoginSuccess = ^(uint32_t uid, int fd) {
        NSLog(@"Login successfully, uid: %u", uid);
        weakSelf.signalUid = uid;
    };
    
    signalEngine.onLoginFailed = ^(AgoraEcode ecode) {
        NSLog(@"Login failed, error: %lu", (unsigned long)ecode);
        dispatch_async(dispatch_get_main_queue(), ^{
            [AlertUtil showAlert:@"Login failed" completion:^{
                [weakSelf.navigationController popViewControllerAnimated:NO];
            }];
        });
    };
    
    signalEngine.onLogout = ^(AgoraEcode ecode) {
        NSLog(@"onLogout, ecode: %lu", (unsigned long)ecode);
        dispatch_async(dispatch_get_main_queue(), ^{
            [weakSelf.navigationController popViewControllerAnimated:NO];
        });
    };
    
    signalEngine.onMessageSendError = ^(NSString* messageID, AgoraEcode ecode) {
        NSLog(@"onMessageSendError, messageID: %@, error: %lu", messageID, (unsigned long)ecode);
    };
    
    signalEngine.onMessageSendSuccess = ^(NSString *messageID) {
        NSLog(@"onMessageSendSuccess, messageID: %@", messageID);
    };
    
    NSString *account = [NSString stringWithFormat:@"signal-demo-iOS-%f", [NSDate date].timeIntervalSinceReferenceDate];
    [signalEngine login:[KeyCenter signalAppId]
                account:account
                  token:[KeyCenter generateSignalToken:account expiredTime:3600]
                    uid:0
               deviceID:nil];
}

// MARK: - WebSocket

- (void)connectWebSocket {
    webSocket.delegate = nil;
    webSocket = nil;
    
    SRWebSocket *newWebSocket = [[SRWebSocket alloc] initWithURL:[NSURL URLWithString:kServerUrlString]];
    newWebSocket.delegate = self;
    [newWebSocket open];
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

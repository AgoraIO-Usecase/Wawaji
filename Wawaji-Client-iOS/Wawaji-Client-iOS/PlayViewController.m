//
//  PlayViewController.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/10/24.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "PlayViewController.h"
#import "KeyCenter.h"
#import "AlertUtil.h"
#import "Constants.h"
#import "NSObject+JSONString.h"
#import <AgoraSignalKit/AgoraSignalKit.h>
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

@interface PlayViewController () <AgoraRtcEngineDelegate>
{
    AgoraAPI *signalEngine;
    NSString *signalChannel;
    
    AgoraRtcEngineKit *mediaEngine;
    NSMutableArray *allStreamUids;
    NSUInteger currentStreamUid;
    
    UIAlertController *startAlertController;
    UIAlertAction *startAlertAction;
    NSTimer *timer;
    NSUInteger countDown;
}

@property (weak, nonatomic) IBOutlet UIView *videoView;
@property (weak, nonatomic) IBOutlet UIView *controlView;
@property (weak, nonatomic) IBOutlet UIButton *cionButton;

@end

@implementation PlayViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.navigationItem.title = self.machine;
    
    allStreamUids = [[NSMutableArray alloc] initWithCapacity:2];
    currentStreamUid = 0;
    
    [self loadMediaEngine];
    [self loadSignalEngine];
    [self joinSignalChannel];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [UIApplication sharedApplication].idleTimerDisabled = NO;
    [mediaEngine leaveChannel:nil];
    mediaEngine = nil;
    
    if (signalChannel) {
        [signalEngine channelLeave:signalChannel];
    }
    signalEngine = nil;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)leave:(id)sender {
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)switchCamera:(id)sender {
    if (allStreamUids.count <= 1) {
        [AlertUtil showAlert:NSLocalizedString(@"NoMoreCamera", nil)];
        return;
    }
    
    AgoraRtcVideoCanvas *videoCanvas = [[AgoraRtcVideoCanvas alloc] init];
    videoCanvas.uid = currentStreamUid;
    videoCanvas.view = nil;
    [mediaEngine setupRemoteVideo:videoCanvas];
    
    NSUInteger index = [allStreamUids indexOfObject:@(currentStreamUid)];
    if (index == allStreamUids.count - 1) {
        index = 0;
    }
    else {
        index++;
    }
    currentStreamUid = [allStreamUids[index] unsignedIntegerValue];
    
    AgoraRtcVideoCanvas *newVideoCanvas = [[AgoraRtcVideoCanvas alloc] init];
    newVideoCanvas.uid = currentStreamUid;
    newVideoCanvas.view = self.videoView;
    newVideoCanvas.renderMode = AgoraRtc_Render_Hidden;
    [mediaEngine setupRemoteVideo:newVideoCanvas];
}

- (IBAction)cion:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"PLAY"};
    [self sendControlMessage:msgDic];
}

- (IBAction)startUp:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"up", @"pressed" : @(YES)};
    [self sendControlMessage:msgDic];
}

- (IBAction)stopUp:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"up", @"pressed" : @(NO)};
    [self sendControlMessage:msgDic];
}

- (IBAction)startDown:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"down", @"pressed" : @(YES)};
    [self sendControlMessage:msgDic];
}

- (IBAction)stopDown:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"down", @"pressed" : @(NO)};
    [self sendControlMessage:msgDic];
}

- (IBAction)startLeft:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"left", @"pressed" : @(YES)};
    [self sendControlMessage:msgDic];
}

- (IBAction)stopLeft:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"left", @"pressed" : @(NO)};
    [self sendControlMessage:msgDic];
}

- (IBAction)startRight:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"right", @"pressed" : @(YES)};
    [self sendControlMessage:msgDic];
}

- (IBAction)stopRight:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"right", @"pressed" : @(NO)};
    [self sendControlMessage:msgDic];
}

- (IBAction)fetch:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CATCH"};
    [self sendControlMessage:msgDic];
}

// MARK: - Media Engine

- (void)loadMediaEngine {
    mediaEngine = [AgoraRtcEngineKit sharedEngineWithAppId:[KeyCenter appId] delegate:self];
    [mediaEngine setChannelProfile:AgoraRtc_ChannelProfile_LiveBroadcasting];
    [mediaEngine setClientRole:AgoraRtc_ClientRole_Broadcaster withKey:nil];
    [mediaEngine enableVideo];
    [mediaEngine enableLocalVideo:NO];
    [mediaEngine enableAudio];
    [mediaEngine muteLocalAudioStream:YES];
    [mediaEngine setParameters:@"{\"che.audio.external_capture\": true}"];
    
    NSString *key = [KeyCenter generateMediaKey:kMediaChannel uid:0 expiredTime:0];
    int result = [mediaEngine joinChannelByKey:key channelName:kMediaChannel info:nil uid:0 joinSuccess:nil];
    if (result == 0) {
        [UIApplication sharedApplication].idleTimerDisabled = YES;
    }
    else {
        NSLog(@"joinChannel failed: %d", result);
        [AlertUtil showAlert:NSLocalizedString(@"JoinChannelFailed", nil) completion:^{
            [self dismissViewControllerAnimated:NO completion:nil];
        }];
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

- (void)rtcEngine:(AgoraRtcEngineKit *)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed {
    NSLog(@"rtcEngine:firstRemoteVideoDecodedOfUid: %ld", (long)uid);
    if ([allStreamUids containsObject:@(uid)]) {
        return;
    }
    
    [allStreamUids addObject:@(uid)];
    if (currentStreamUid == 0) {
        currentStreamUid = uid;
        
        AgoraRtcVideoCanvas *videoCanvas = [[AgoraRtcVideoCanvas alloc] init];
        videoCanvas.uid = currentStreamUid;
        videoCanvas.view = self.videoView;
        videoCanvas.renderMode = AgoraRtc_Render_Hidden;
        [mediaEngine setupRemoteVideo:videoCanvas];
    }
}

- (void)rtcEngine:(AgoraRtcEngineKit *)engine didOfflineOfUid:(NSUInteger)uid reason:(AgoraRtcUserOfflineReason)reason {
    NSLog(@"rtcEngine:didOfflineOfUid: %ld", (long)uid);
}

// MARK: - Signal Engine

- (void)loadSignalEngine {
    __weak typeof(self) weakSelf = self;
    
    signalEngine = [AgoraAPI getInstanceWithoutMedia:[KeyCenter appId]];
    signalEngine.onChannelAttrUpdated = ^(NSString* channelID, NSString* name, NSString* value, NSString* type) {
        NSLog(@"onChannelAttrUpdated, name : %@, value : %@, type : %@", name, value, type);
        if (![type isEqualToString:@"set"]) {
            NSData *data = [value dataUsingEncoding:NSUTF8StringEncoding];
            NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];

            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf updateUI:dic[@"playing"] queue:dic[@"queue"]];
            });
        }
    };
    
    signalEngine.onMessageInstantReceive = ^(NSString *account, uint32_t uid, NSString *msg) {
        NSLog(@"onMessageInstantReceive, msg: %@", msg);
        
        NSData *data = [msg dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *result = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
        NSString *type = result[@"type"];
        if ([type isEqualToString:@"PREPARE"]) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf startPlay];
            });
        }
    };
}

- (void)joinSignalChannel {
    signalChannel = [NSString stringWithFormat:@"room_%@", self.machine];
    [signalEngine channelJoin:signalChannel];
}

- (void)sendControlMessage:(NSDictionary *)msgDic {
    NSString *msgString = [msgDic JSONString];
    NSLog(@"messageChannelSend: %@", msgString);
    [signalEngine messageChannelSend:signalChannel msg:msgString msgID:nil];
}

- (void)updateUI:(NSString *)playing queue:(NSArray *)queue {
    if ([self.account isEqualToString:playing]) {
        self.controlView.userInteractionEnabled = YES;
        self.cionButton.enabled = NO;
        
        NSString *title = NSLocalizedString(@"Gaming", nil);
        [self.cionButton setTitle:title forState:UIControlStateNormal];
    }
    else {
        self.controlView.userInteractionEnabled = NO;
        
        NSUInteger index = [queue indexOfObject:self.account];
        if (index != NSNotFound) {
            self.cionButton.enabled = NO;

            NSString *title = [NSString stringWithFormat:NSLocalizedString(@"Waiting", nil), index + 1];
            [self.cionButton setTitle:title forState:UIControlStateNormal];
        }
        else {
            self.cionButton.enabled = YES;
            
            if (queue.count > 0) {
                NSString *title = [NSString stringWithFormat:NSLocalizedString(@"CionAndWait", nil), queue.count + 1];
                [self.cionButton setTitle:title forState:UIControlStateNormal];
            }
            else if (playing.length > 0) {
                NSString *title = [NSString stringWithFormat:NSLocalizedString(@"CionAndWait", nil), 1];
                [self.cionButton setTitle:title forState:UIControlStateNormal];
            }
            else {
                NSString *title = NSLocalizedString(@"Cion", nil);
                [self.cionButton setTitle:title forState:UIControlStateNormal];
            }
        }
    }
}

- (void)startPlay {
    countDown = 10;
    timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(countDownTimer) userInfo:nil repeats:YES];
    
    startAlertController = [UIAlertController alertControllerWithTitle:nil
                                                                             message:NSLocalizedString(@"YourTurn", nil)
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    
    NSString *startTitle = [NSString stringWithFormat:NSLocalizedString(@"StartPlay", nil), countDown];
    startAlertAction = [UIAlertAction actionWithTitle:startTitle style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        [timer invalidate];
        timer = nil;
        startAlertController = nil;
        startAlertAction = nil;

        NSDictionary *msgDic = @{@"type" : @"START"};
        NSString *msgString = [msgDic JSONString];
        NSLog(@"messageInstantSend: %@", msgString);
        [signalEngine messageInstantSend:self.machine uid:0 msg:msgString msgID:nil];
    }];
    [startAlertController addAction:startAlertAction];

    UIAlertAction *giveUpAlertAction = [UIAlertAction actionWithTitle:NSLocalizedString(@"GiveUp", nil) style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
        [timer invalidate];
        timer = nil;
        startAlertController = nil;
        startAlertAction = nil;
    }];
    [startAlertController addAction:giveUpAlertAction];

    [self presentViewController:startAlertController animated:YES completion:nil];
}

- (void)countDownTimer {
    countDown--;
    
    if (countDown > 0) {
        NSString *startTitle = [NSString stringWithFormat:NSLocalizedString(@"StartPlay", nil), countDown];
        [startAlertAction setValue:startTitle forKeyPath:@"title"];
    }
    else {
        [timer invalidate];
        timer = nil;
        
        [startAlertController dismissViewControllerAnimated:YES completion:nil];
        startAlertController = nil;
        startAlertAction = nil;
    }
}

@end

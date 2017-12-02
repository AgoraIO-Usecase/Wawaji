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
#import "WawajiControllerCreator.h"
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

static const WawajiManufacturer kWawajiManufacturer = WawajiManufacturer_LeYaoYao;

@interface PlayViewController () <AgoraRtcEngineDelegate>
{
    id<WawajiController> wawajiController;
    
    AgoraRtcEngineKit *mediaEngine;
    NSMutableArray *allStreamUids;
    NSUInteger currentStreamUid;
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
    
    allStreamUids = [[NSMutableArray alloc] initWithCapacity:2];
    currentStreamUid = 0;
    
    [self loadMediaEngine];
    
    if (self.player) {
        wawajiController = [WawajiControllerCreator getWawajiController:kWawajiManufacturer];
        [wawajiController initialize];
        if ([wawajiController respondsToSelector:@selector(setFetchResultBlock:)]) {
            wawajiController.fetchResultBlock = ^(BOOL result) {
                if (result) {
                    [AlertUtil showAlert:NSLocalizedString(@"FetchSuccess", nil)];
                }
                else {
                    [AlertUtil showAlert:NSLocalizedString(@"FetchFailed", nil)];
                }
            };
        }
    }
    else {
        [self.controlView removeFromSuperview];
    }
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    [UIApplication sharedApplication].idleTimerDisabled = NO;
    [mediaEngine leaveChannel:nil];
    mediaEngine = nil;
    wawajiController = nil;
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
    [wawajiController insertCion];
}

- (IBAction)startMoveUp:(id)sender {
    if (![wawajiController startMoveUp]) {
        [AlertUtil showAlert:NSLocalizedString(@"PleaseInsertCion", nil)];
    }
}

- (IBAction)stopMoveUp:(id)sender {
    [wawajiController stopMoveUp];
}

- (IBAction)startMoveDown:(id)sender {
    if (![wawajiController startMoveDown]) {
        [AlertUtil showAlert:NSLocalizedString(@"PleaseInsertCion", nil)];
    }
}

- (IBAction)stopMoveDown:(id)sender {
    [wawajiController stopMoveDown];
}

- (IBAction)startMoveLeft:(id)sender {
    if (![wawajiController startMoveLeft]) {
        [AlertUtil showAlert:NSLocalizedString(@"PleaseInsertCion", nil)];
    }
}

- (IBAction)stopMoveLeft:(id)sender {
    [wawajiController stopMoveLeft];
}

- (IBAction)startMoveRight:(id)sender {
    if (![wawajiController startMoveRight]) {
        [AlertUtil showAlert:NSLocalizedString(@"PleaseInsertCion", nil)];
    }
}

- (IBAction)stopMoveRight:(id)sender {
    [wawajiController stopMoveRight];
}

- (IBAction)fetch:(id)sender {
    if (![wawajiController fetch]) {
        [AlertUtil showAlert:NSLocalizedString(@"PleaseInsertCion", nil)];
    }
}

// MARK: - Media Engine

- (void)loadMediaEngine {
    mediaEngine = [AgoraRtcEngineKit sharedEngineWithAppId:kAppID delegate:self];
    [mediaEngine setChannelProfile:AgoraRtc_ChannelProfile_LiveBroadcasting];
    [mediaEngine setClientRole:AgoraRtc_ClientRole_Broadcaster withKey:nil];
    [mediaEngine enableVideo];
    [mediaEngine enableLocalVideo:NO];
    [mediaEngine enableAudio];
    [mediaEngine muteLocalAudioStream:YES];
    [mediaEngine setParameters:@"{\"che.audio.external_capture\": true}"];
    
    int result = [mediaEngine joinChannelByKey:nil channelName:self.channel info:nil uid:0 joinSuccess:nil];
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
//    NSLog(@"rtcEngine:didOccurWarning: %ld", (long)warningCode);
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

@end

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
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

@interface PlayViewController () <AgoraRtcEngineDelegate>
{
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
    
    self.navigationItem.title = self.channel;
    
    allStreamUids = [[NSMutableArray alloc] initWithCapacity:2];
    currentStreamUid = 0;
    
    [self loadMediaEngine];
    
    NSLog(@"--- connect to Wawaji if needed ---");
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [UIApplication sharedApplication].idleTimerDisabled = NO;
    [mediaEngine leaveChannel:nil];
    mediaEngine = nil;
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
    NSLog(@"--- send cion command to wawaji ---");
    [AlertUtil showAlert:@"Please add control module"];
}

- (IBAction)startUp:(id)sender {
    NSLog(@"--- send move up command to wawaji ---");
}

- (IBAction)stopUp:(id)sender {
    NSLog(@"--- send stop move up command to wawaji ---");
    [AlertUtil showAlert:@"Please add control module"];
}

- (IBAction)startDown:(id)sender {
    NSLog(@"--- send move up command to wawaji ---");
}

- (IBAction)stopDown:(id)sender {
    NSLog(@"--- send stop move down command to wawaji ---");
    [AlertUtil showAlert:@"Please add control module"];
}

- (IBAction)startLeft:(id)sender {
    NSLog(@"--- send move left command to wawaji ---");
}

- (IBAction)stopLeft:(id)sender {
    NSLog(@"--- send stop move left command to wawaji ---");
    [AlertUtil showAlert:@"Please add control module"];
}

- (IBAction)startRight:(id)sender {
    NSLog(@"--- send move right command to wawaji ---");
    
}

- (IBAction)stopRight:(id)sender {
    NSLog(@"--- send stop move right command to wawaji ---");
    [AlertUtil showAlert:@"Please add control module"];
}

- (IBAction)fetch:(id)sender {
    NSLog(@"--- send catch command to wawaji ---");
    [AlertUtil showAlert:@"Please add control module"];
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
    //NSLog(@"rtcEngine:didOccurWarning: %ld", (long)warningCode);
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

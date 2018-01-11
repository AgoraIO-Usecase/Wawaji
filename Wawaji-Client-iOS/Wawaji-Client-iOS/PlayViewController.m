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
#import "NSObject+JSONString.h"
#import <AgoraSignalKit/AgoraSignalKit.h>
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

typedef NS_ENUM(NSInteger, PlayStatus) {
    PlayStatus_Initial,
    PlayStatus_Waiting,
    PlayStatus_Ready,
    PlayStatus_Playing,
    PlayStatus_Finish,
};

@interface PlayViewController () <AgoraRtcEngineDelegate>
{
    AVAudioPlayer *musicPlayer;
    AVAudioPlayer *effectPlayer;
    
    AgoraAPI *signalEngine;
    NSString *signalChannel;
    
    AgoraRtcEngineKit *mediaEngine;
    NSMutableArray *allStreamUids;
    NSUInteger currentStreamUid;
    
    UIAlertController *startAlertController;
    UIAlertAction *startAlertAction;
    NSTimer *timer;
    unsigned int countDown;
}

@property (weak, nonatomic) IBOutlet UIView *videoView;
@property (weak, nonatomic) IBOutlet UIView *watchView;
@property (weak, nonatomic) IBOutlet UILabel *queueLabel;
@property (weak, nonatomic) IBOutlet UIButton *startButton;
@property (weak, nonatomic) IBOutlet UIView *promptView;
@property (weak, nonatomic) IBOutlet UIView *promptBackgroundView;
@property (weak, nonatomic) IBOutlet UILabel *promptLabel;
@property (weak, nonatomic) IBOutlet UIView *controlView;
@property (weak, nonatomic) IBOutlet UIButton *fetchButton;
@property (weak, nonatomic) IBOutlet UILabel *userNumberLabel;

@property (assign, nonatomic) NSUInteger userNumber;
@property (assign, nonatomic) PlayStatus status;

@end

@implementation PlayViewController
@synthesize status;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    allStreamUids = [[NSMutableArray alloc] initWithCapacity:2];
    currentStreamUid = 0;
    
    [self playMusic];
    [self loadMediaEngine];
    [self loadSignalEngine];
    [self joinSignalChannel];
    [self queueUserNum];
}

- (void)playMusic {
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:AVAudioSessionCategoryOptionDefaultToSpeaker error:nil];
    [[AVAudioSession sharedInstance] setActive:YES error:nil];
    [[AVAudioSession sharedInstance] setMode:AVAudioSessionModeVideoChat error:nil];
    
    NSURL *url = [[NSBundle mainBundle] URLForResource:@"music" withExtension:@"mp3"];
    musicPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:nil];
    musicPlayer.numberOfLoops = -1;
    [musicPlayer play];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
    
    [UIApplication sharedApplication].idleTimerDisabled = NO;
    [mediaEngine leaveChannel:^(AgoraRtcStats *stat) {
        [AgoraRtcEngineKit destroy];
    }];
    mediaEngine = nil;
    
    if (signalChannel) {
        [signalEngine channelLeave:signalChannel];
    }
    signalEngine = nil;
    
    [timer invalidate];
    timer = nil;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
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

- (IBAction)start:(id)sender {
    if (status == PlayStatus_Initial) {
        NSDictionary *msgDic = @{@"type" : @"PLAY"};
        [self sendChannelMessage:msgDic];
        
        if (effectPlayer) {
            [effectPlayer stop];
        }
        NSURL *url = [[NSBundle mainBundle] URLForResource:@"start" withExtension:@"m4a"];
        effectPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:nil];
        [effectPlayer play];
    }
    else if (status == PlayStatus_Ready) {
        NSDictionary *msgDic = @{@"type" : @"START"};
        [self sendInstantMessage:msgDic];
        
        self.promptView.hidden = YES;
        self.watchView.hidden = YES;
        self.controlView.hidden = NO;
        
        status = PlayStatus_Playing;
        countDown = 30;
        NSString *title = [NSString stringWithFormat:@"(%d)", countDown];
        [self.fetchButton setTitle:title forState:UIControlStateNormal];
        
        if (effectPlayer) {
            [effectPlayer stop];
        }
        NSURL *url = [[NSBundle mainBundle] URLForResource:@"start" withExtension:@"m4a"];
        effectPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:nil];
        [effectPlayer play];
    }
    else if (status == PlayStatus_Finish) {
        self.promptBackgroundView.hidden = YES;
        self.promptView.hidden = YES;
        self.queueLabel.hidden = NO;
        
        NSString *startTitle = self.queueLabel.text.length > 0 ? NSLocalizedString(@"Prebook", nil) : NSLocalizedString(@"Start", nil);
        [self.startButton setTitle:startTitle forState:UIControlStateNormal];
        
        status = PlayStatus_Initial;
    }
}

- (IBAction)startUp:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"up", @"pressed" : @(YES)};
    [self sendChannelMessage:msgDic];
}

- (IBAction)stopUp:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"up", @"pressed" : @(NO)};
    [self sendChannelMessage:msgDic];
}

- (IBAction)startDown:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"down", @"pressed" : @(YES)};
    [self sendChannelMessage:msgDic];
}

- (IBAction)stopDown:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"down", @"pressed" : @(NO)};
    [self sendChannelMessage:msgDic];
}

- (IBAction)startLeft:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"left", @"pressed" : @(YES)};
    [self sendChannelMessage:msgDic];
}

- (IBAction)stopLeft:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"left", @"pressed" : @(NO)};
    [self sendChannelMessage:msgDic];
}

- (IBAction)startRight:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"right", @"pressed" : @(YES)};
    [self sendChannelMessage:msgDic];
}

- (IBAction)stopRight:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CONTROL", @"data" : @"right", @"pressed" : @(NO)};
    [self sendChannelMessage:msgDic];
}

- (IBAction)fetch:(id)sender {
    NSDictionary *msgDic = @{@"type" : @"CATCH"};
    [self sendChannelMessage:msgDic];
}

// MARK: - Media Engine

- (void)loadMediaEngine {
    mediaEngine = [AgoraRtcEngineKit sharedEngineWithAppId:[KeyCenter appId] delegate:self];
    [mediaEngine setChannelProfile:AgoraRtc_ChannelProfile_LiveBroadcasting];
    [mediaEngine setClientRole:AgoraRtc_ClientRole_Broadcaster withKey:nil];
    [mediaEngine enableVideo];
    [mediaEngine enableLocalVideo:NO];
    [mediaEngine disableAudio];
    [mediaEngine setParameters:@"{\"che.audio.external_device\":true}"];
    
    NSString *key = [KeyCenter generateMediaKey:self.wawaji.videoChannel uid:0 expiredTime:0];
    int result = [mediaEngine joinChannelByKey:key channelName:self.wawaji.videoChannel info:nil uid:0 joinSuccess:nil];
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
                NSString *playing = dic[@"playing"] == [NSNull null] ? nil : dic[@"playing"];
                [weakSelf updateUI:playing queue:dic[@"queue"]];
            });
        }
    };
    
    signalEngine.onMessageInstantReceive = ^(NSString *account, uint32_t uid, NSString *msg) {
        if (![account isEqualToString:weakSelf.wawaji.name]) {
            return;
        }
        
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
    
    signalEngine.onMessageChannelReceive = ^(NSString* channelID, NSString* account, uint32_t uid, NSString* msg) {
        if (![account isEqualToString:weakSelf.wawaji.name]) {
            return;
        }
        
        NSLog(@"onMessageChannelReceive, msg: %@", msg);
        
        if (weakSelf.status != PlayStatus_Playing) {
            return;
        }
        
        NSData *data = [msg dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *result = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
        NSString *type = result[@"type"];
        NSString *player = result[@"player"];
        if ([type isEqualToString:@"RESULT"] && [player isEqualToString:weakSelf.account]) {
            BOOL success = [result[@"data"] boolValue];
            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf finishPlay:success];
            });
        }
    };
    
    signalEngine.onChannelQueryUserNumResult = ^(NSString* channelID, AgoraEcode ecode, int num) {
        if (ecode == AgoraEcode_SUCCESS) {
            NSLog(@"Query user num successfully, channel: %@, num: %d", channelID, num);
            dispatch_async(dispatch_get_main_queue(), ^{
                weakSelf.userNumber = num;
                weakSelf.userNumberLabel.text = [NSString stringWithFormat:NSLocalizedString(@"RoomPeopleNumber", nil), num];
                weakSelf.userNumberLabel.hidden = NO;
            });
        } else {
            NSLog(@"Query user num failed, channel: %@, error: %lu",  channelID, (unsigned long)ecode);
        }
    };

    signalEngine.onChannelUserJoined = ^(NSString* account, uint32_t uid) {
        NSLog(@"onChannelUserJoined, account: %@, uid: %d", account, uid);
        dispatch_async(dispatch_get_main_queue(), ^{
            weakSelf.userNumber = weakSelf.userNumber + 1;
            weakSelf.userNumberLabel.text = [NSString stringWithFormat:NSLocalizedString(@"RoomPeopleNumber", nil), weakSelf.userNumber];
        });
    };
    
    signalEngine.onChannelUserLeaved = ^(NSString* account, uint32_t uid) {
        NSLog(@"onChannelUserLeaved, account: %@, uid: %d", account, uid);
        dispatch_async(dispatch_get_main_queue(), ^{
            weakSelf.userNumber = weakSelf.userNumber - 1;
            weakSelf.userNumberLabel.text = [NSString stringWithFormat:NSLocalizedString(@"RoomPeopleNumber", nil), weakSelf.userNumber];
        });
    };
}

- (void)joinSignalChannel {
    signalChannel = [NSString stringWithFormat:@"room_%@", self.wawaji.name];
    [signalEngine channelJoin:signalChannel];
}

- (void)queueUserNum {
    [signalEngine channelQueryUserNum:signalChannel];
}

- (void)sendChannelMessage:(NSDictionary *)msgDic {
    NSString *msgString = [msgDic JSONString];
    NSLog(@"sendChannelMessage: %@", msgString);
    [signalEngine messageChannelSend:signalChannel msg:msgString msgID:nil];
}

- (void)sendInstantMessage:(NSDictionary *)msgDic {
    NSString *msgString = [msgDic JSONString];
    NSLog(@"sendInstantMessage: %@", msgString);
    [signalEngine messageInstantSend:self.wawaji.name uid:0 msg:msgString msgID:nil];
}

- (void)updateUI:(NSString *)playing queue:(NSArray *)queue {
    if ([playing isEqualToString:self.account]) {
        if (status == PlayStatus_Initial) {
            self.watchView.hidden = YES;
            self.controlView.hidden = NO;
            
            status = PlayStatus_Playing;
            countDown = 30;
            NSString *title = [NSString stringWithFormat:@"(%d)", countDown];
            [self.fetchButton setTitle:title forState:UIControlStateNormal];
            
            timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(countDownTimer) userInfo:nil repeats:YES];
        }
        else if (status == PlayStatus_Waiting) {
            self.queueLabel.text = nil;
        }
    }
    else {
        if (status == PlayStatus_Ready) {
            self.promptView.hidden = YES;
            status = PlayStatus_Initial;
            
            [timer invalidate];
            timer = nil;
        }
        
        NSUInteger index = [queue indexOfObject:self.account];
        if (queue && index != NSNotFound) {
            self.queueLabel.text = [NSString stringWithFormat:NSLocalizedString(@"QueueInfo", nil), index + 1];
            
            if (status == PlayStatus_Initial) {
                status = PlayStatus_Waiting;

                [self.startButton setTitle:NSLocalizedString(@"Start", nil) forState:UIControlStateNormal];
                self.startButton.enabled = NO;
            }
        }
        else {
            self.startButton.enabled = YES;
            
            if (queue.count > 0) {
                self.queueLabel.text = [NSString stringWithFormat:NSLocalizedString(@"QueueInfo", nil), queue.count + 1];
                
                if (status == PlayStatus_Initial) {
                    [self.startButton setTitle:NSLocalizedString(@"Prebook", nil) forState:UIControlStateNormal];
                }
            }
            else if (playing.length > 0) {
                self.queueLabel.text = [NSString stringWithFormat:NSLocalizedString(@"QueueInfo", nil), 1];
                
                if (status == PlayStatus_Initial) {
                    [self.startButton setTitle:NSLocalizedString(@"Prebook", nil) forState:UIControlStateNormal];
                }
            }
            else {
                self.queueLabel.text = nil;
                
                if (status == PlayStatus_Initial) {
                    [self.startButton setTitle:NSLocalizedString(@"Start", nil) forState:UIControlStateNormal];
                }
            }
        }
    }
}

- (void)startPlay {
    status = PlayStatus_Ready;
    
    self.promptLabel.text = NSLocalizedString(@"YourTurn", nil);
    self.promptView.hidden = NO;
    self.startButton.enabled = YES;
    
    countDown = 10;
    NSString *startTitle = [NSString stringWithFormat:NSLocalizedString(@"StartPlay", nil), countDown];
    [self.startButton setTitle:startTitle forState:UIControlStateNormal];
    
    timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(countDownTimer) userInfo:nil repeats:YES];
}

- (void)finishPlay:(BOOL)success {
    if (status != PlayStatus_Playing) {
        return;
    }
    
    [timer invalidate];
    timer = nil;
    
    NSString *promptLabelTest;
    NSString *effectFileName;
    if (success) {
        promptLabelTest = NSLocalizedString(@"Success", nil);
        effectFileName = @"success";
    }
    else {
        promptLabelTest = NSLocalizedString(@"Failed", nil);
        effectFileName = @"failed";
    }
    
    self.controlView.hidden = YES;
    self.watchView.hidden = NO;
    
    self.promptBackgroundView.hidden = NO;
    self.promptView.hidden = NO;
    self.promptLabel.text = promptLabelTest;
    
    self.queueLabel.hidden = YES;
    
    NSString *startTitle = NSLocalizedString(@"TryAgain", nil);
    [self.startButton setTitle:startTitle forState:UIControlStateNormal];
    
    if (effectPlayer) {
        [effectPlayer stop];
    }
    NSURL *url = [[NSBundle mainBundle] URLForResource:effectFileName withExtension:@"mp3"];
    effectPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:nil];
    [effectPlayer play];
    
    status = PlayStatus_Finish;
}

- (void)countDownTimer {
    countDown--;
    
    if (countDown > 0) {
        if (status == PlayStatus_Ready) {
            NSString *title = [NSString stringWithFormat:NSLocalizedString(@"StartPlay", nil), countDown];
            [self.startButton setTitle:title forState:UIControlStateNormal];
        }
        else if (status == PlayStatus_Playing) {
            NSString *title = [NSString stringWithFormat:@"(%ds)", countDown];
            [self.fetchButton setTitle:title forState:UIControlStateNormal];
        }
    }
    else {
        if (status == PlayStatus_Playing) {
            [self.fetchButton setTitle:@"(0s)" forState:UIControlStateNormal];
        }
        
        [timer invalidate];
        timer = nil;
    }
}

@end

//
//  ListViewController.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/11/23.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "ListViewController.h"
#import "PlayViewController.h"
#import "NSObject+JSONString.h"
#import "AlertUtil.h"
#import "KeyCenter.h"
#import "WawajiInfo.h"
#import <AgoraSignalKit/AgoraSignalKit.h>

static NSString * const kControlServer = @"wawaji_cc_server_agora";

@interface ListViewController () <UICollectionViewDataSource, UICollectionViewDelegate>
{
    AgoraAPI *signalEngine;
    NSString *account;
}

@property (weak, nonatomic) IBOutlet UICollectionView *collectionView;
@property (strong, nonatomic) NSArray *machines;

@end

@implementation ListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self loadSignalEngine];
}

- (void)viewWillAppear:(BOOL)animated {
    if (account == nil) {
        account = [NSString stringWithFormat:@"wawaji-demo-iOS-%f", [NSDate date].timeIntervalSinceReferenceDate];
        [self login];
    }
    else {
        [self.collectionView reloadData];
        [self getDeviceList];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"playSegue"]) {
        NSIndexPath *indexPath = self.collectionView.indexPathsForSelectedItems[0];
        PlayViewController *vc = (PlayViewController *)segue.destinationViewController;
        vc.account = account;
        vc.wawaji = self.machines[indexPath.item];
    }
}

- (IBAction)unwindToListView:(UIStoryboardSegue*)sender
{
}

#pragma mark - Collection view data source

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.machines.count;
}

- (UICollectionReusableView *)collectionView:(UICollectionView *)collectionView viewForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath
{
    UICollectionReusableView *reusableview = nil;
    
    if (kind == UICollectionElementKindSectionHeader) {
        UICollectionReusableView *headerView = [collectionView dequeueReusableSupplementaryViewOfKind:UICollectionElementKindSectionHeader withReuseIdentifier:@"HeaderView" forIndexPath:indexPath];
        reusableview = headerView;
    }
    
    return reusableview;
}

- (CGSize)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout*)collectionViewLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    CGFloat width = (self.collectionView.frame.size.width - 24) / 2;
    return CGSizeMake(width, width);
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"CollectionViewCell" forIndexPath:indexPath];
    UILabel *nameLabel = [cell viewWithTag:102];
    UIButton *statusButton = [cell viewWithTag:104];
    
    // Configure the cell
    WawajiInfo *wawaji = self.machines[indexPath.item];
    nameLabel.text = wawaji.name;
    statusButton.selected = wawaji.isBusy;
    
    return cell;
}

#pragma mark -

- (void)loadSignalEngine {
    __weak typeof(self) weakSelf = self;
    
    signalEngine = [AgoraAPI getInstanceWithoutMedia:[KeyCenter appId]];
    signalEngine.onLog = ^(NSString *txt){
        //NSLog(@"%@", txt);
    };
    
    signalEngine.onLoginSuccess = ^(uint32_t uid, int fd) {
        NSLog(@"Login successfully, uid: %u", uid);
        [weakSelf getDeviceList];
    };
    
    signalEngine.onLoginFailed = ^(AgoraEcode ecode) {
        NSLog(@"Login failed, error: %lu", (unsigned long)ecode);
        dispatch_async(dispatch_get_main_queue(), ^{
            [AlertUtil showAlert:@"Login failed"];
        });
    };
    
    signalEngine.onLogout = ^(AgoraEcode ecode) {
        NSLog(@"onLogout, ecode: %lu", (unsigned long)ecode);
        dispatch_async(dispatch_get_main_queue(), ^{
            [weakSelf login];
        });
    };
    
    signalEngine.onMessageSendError = ^(NSString* messageID, AgoraEcode ecode) {
        NSLog(@"onMessageSendError, error: %lu", (unsigned long)ecode);
    };
    
    signalEngine.onMessageSendSuccess = ^(NSString *messageID) {
        NSLog(@"onMessageSendSuccess");
    };
    
    signalEngine.onMessageInstantReceive = ^(NSString *account, uint32_t uid, NSString *msg) {
        NSLog(@"onMessageInstantReceive, msg: %@", msg);
        
        NSData *data = [msg dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *result = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
        if ([result[@"type"] isEqualToString:@"LIST"]) {
            NSArray *deviceArray = result[@"machines"];
            NSMutableArray *devices = [[NSMutableArray alloc] initWithCapacity:deviceArray.count];
            for(NSDictionary *device in deviceArray) {
                WawajiInfo *wawaji = [[WawajiInfo alloc] init];
                wawaji.name = device[@"name"];
                wawaji.videoChannel = device[@"video_channel"];
                wawaji.isBusy = ((NSArray *)device[@"players"]).count > 0;
                [devices addObject:wawaji];
            }
            
            dispatch_async(dispatch_get_main_queue(), ^{
                weakSelf.machines = devices;
                [weakSelf.collectionView reloadData];
            });
        }
    };
}

- (void)login {
    [signalEngine login:[KeyCenter appId]
                account:account
                  token:[KeyCenter generateSignalToken:account expiredTime:3600]
                    uid:0
               deviceID:nil];
}

- (void)getDeviceList {
    NSDictionary *msgDic = @{@"type" : @"LIST"};
    NSString *msgString = [msgDic JSONString];
    NSLog(@"messageInstantSend: %@", msgString);
    [signalEngine messageInstantSend:kControlServer uid:0 msg:msgString msgID:nil];
}

@end

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
#import "Constants.h"
#import <AgoraSignalKit/AgoraSignalKit.h>

@interface ListViewController ()
{
    AgoraAPI *signalEngine;
    NSString *account;
}
@property (strong, nonatomic) NSArray *machines;
@end

@implementation ListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self loadSignalEngine];
    [self login];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.machines.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"TableViewCell"];
    cell.textLabel.text = self.machines[indexPath.row];
    return cell;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"playSegue"]) {
        PlayViewController *vc = (PlayViewController *)segue.destinationViewController;
        vc.account = account;
        vc.machine = self.machines[self.tableView.indexPathForSelectedRow.row];
    }
}

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
            [AlertUtil showAlert:@"You have been logged out" completion:^{
                [weakSelf.navigationController popToRootViewControllerAnimated:NO];
            }];
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
                [devices addObject:device[@"name"]];
            }
            
            dispatch_async(dispatch_get_main_queue(), ^{
                weakSelf.machines = devices;
                [weakSelf.tableView reloadData];
            });
        }
    };
}

- (void)login {
    account = [NSString stringWithFormat:@"signal-demo-iOS-%f", [NSDate date].timeIntervalSinceReferenceDate];
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

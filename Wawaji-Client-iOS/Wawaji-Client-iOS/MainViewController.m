//
//  MainViewController.m
//  Wawaji-Client-iOS
//
//  Created by suleyu on 2017/10/24.
//  Copyright © 2017 Agora. All rights reserved.
//

#import "MainViewController.h"
#import "PlayViewController.h"

@interface MainViewController () <UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *channelTextField;

@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"playSegue"]) {
        PlayViewController *vc = (PlayViewController *)segue.destinationViewController;
        vc.channel = self.channelTextField.text;
    }
}

@end

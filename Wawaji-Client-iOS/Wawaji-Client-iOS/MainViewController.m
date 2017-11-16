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

- (IBAction)start:(id)sender {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil
                                                                             message:@"Would you like to play or just watch?"
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *playAction = [UIAlertAction actionWithTitle:@"Play" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        [self performSegueWithIdentifier:@"playSegue" sender:action];
    }];
    [alertController addAction:playAction];
    
    UIAlertAction *watchAction = [UIAlertAction actionWithTitle:@"Watch" style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
        [self performSegueWithIdentifier:@"playSegue" sender:action];
    }];
    [alertController addAction:watchAction];
    
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleDefault handler:nil];
    [alertController addAction:cancelAction];
    
    [self presentViewController:alertController animated:YES completion:nil];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"playSegue"]) {
        PlayViewController *vc = (PlayViewController *)segue.destinationViewController;
        UIAlertAction *action = (UIAlertAction *)sender;
        vc.player = [action.title isEqualToString:@"Play"];
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [self start:nil];
    return YES;
}

@end

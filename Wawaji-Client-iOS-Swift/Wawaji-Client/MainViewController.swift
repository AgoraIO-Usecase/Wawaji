//
//  MainViewController.swift
//  Wawaji-Client
//
//  Created by suleyu on 2017/11/22.
//  Copyright © 2017 Agora. All rights reserved.
//

import UIKit

class MainViewController: UIViewController {

    @IBOutlet weak var channelTextField: UITextField!

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "playSegue" {
            let vc = segue.destination as! PlayViewController
            vc.channel = channelTextField.text
        }
    }
}

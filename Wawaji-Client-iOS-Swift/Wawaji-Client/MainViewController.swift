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

    @IBAction func start(_ sender: Any) {
        let alertController = UIAlertController(title: nil, message: NSLocalizedString("PlayOrWatchMessage", comment: ""), preferredStyle: .alert)
        let playAction = UIAlertAction(title: NSLocalizedString("Play", comment: ""), style: .default) { action in
            self.performSegue(withIdentifier: "playSegue", sender: action)
        }
        let watchAction = UIAlertAction(title: NSLocalizedString("Watch", comment: ""), style: .default) { action in
            self.performSegue(withIdentifier: "playSegue", sender: action)
        }
        let cancelAction = UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .default, handler: nil)
        
        alertController.addAction(playAction)
        alertController.addAction(watchAction)
        alertController.addAction(cancelAction)
        
        self.present(alertController, animated: true, completion: nil)
    }

    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "playSegue" {
            let vc = segue.destination as! PlayViewController
            let action = sender as! UIAlertAction
            vc.player = action.title == NSLocalizedString("Play", comment: "")
            vc.channel = channelTextField.text
        }
    }
}

extension MainViewController : UITextFieldDelegate {
    public func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        self.start(textField)
        return true
    }
}

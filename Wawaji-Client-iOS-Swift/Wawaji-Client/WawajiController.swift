//
//  WawajiController.swift
//  Wawaji-Client
//
//  Created by suleyu on 2017/12/1.
//  Copyright © 2017 Agora. All rights reserved.
//

import Foundation

protocol WawajiController {

    func initialize()
    
    func insertCion()
    
    func startMoveUp() -> Bool
    
    func stopMoveUp() -> Bool
    
    func startMoveDown() -> Bool
    
    func stopMoveDown() -> Bool
    
    func startMoveLeft() -> Bool
    
    func stopMoveLeft() -> Bool
    
    func startMoveRight() -> Bool
    
    func stopMoveRight() -> Bool
    
    func fetch() -> Bool
    
    var fetchResult : ((Bool) -> Void)? {get set}
}

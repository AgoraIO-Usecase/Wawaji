//
//  WawajiControllerCreator.swift
//  Wawaji-Client
//
//  Created by suleyu on 2017/12/1.
//  Copyright © 2017 Agora. All rights reserved.
//

import Foundation

 enum WawajiManufacturer {
    case LeYaoYao
    case ZiNian
 }

 class WawajiControllerCreator {

    class func getWawajiController(manufacturer: WawajiManufacturer) ->WawajiController {
        switch manufacturer {
        case .LeYaoYao:
            return LeyaoyaoWawajiController()

        case .ZiNian:
            return ZinianWawajiController()
        }
    }
 }

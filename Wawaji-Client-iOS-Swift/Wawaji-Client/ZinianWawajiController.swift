//
//  ZinianWawajiController.swift
//  Wawaji-Client
//
//  Created by suleyu on 2017/12/1.
//  Copyright © 2017 Agora. All rights reserved.
//

import Foundation
import SocketRocket

class ZinianWawajiController: NSObject, WawajiController {
    let webSocketUrl: String = "Your Wawaji Controlling WebSocket Url"
    
    var webSocket : SRWebSocket?
    var fetchResult : ((Bool) -> Void)?
    
    deinit {
        webSocket?.close()
        webSocket?.delegate = nil
        webSocket = nil
    }
    
    func initialize() {
        connectWebSocket()
    }
    
    func insertCion() {
        let messageDic : [String : Any] = ["type" : "Insert", "data" : "", "extra" : 123456]
        sendWebSocketMessage(messageDic)
    }
    
    func startMoveUp() -> Bool {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "u"]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func stopMoveUp() -> Bool {
        return false
    }
    
    func startMoveDown() -> Bool {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "d"]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func stopMoveDown() -> Bool {
        return false
    }
    
    func startMoveLeft() -> Bool {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "l"]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func stopMoveLeft() -> Bool {
        return false
    }
    
    func startMoveRight() -> Bool {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "r"]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func stopMoveRight() -> Bool {
        return false
    }
    
    func fetch() -> Bool {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "b"]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    private func connectWebSocket() {
        if let oldWebSocket = webSocket {
            oldWebSocket.close()
            oldWebSocket.delegate = nil
            webSocket = nil
        }
        
        let newWebSocket = SRWebSocket(url: URL(string: webSocketUrl))
        newWebSocket!.delegate = self
        newWebSocket!.open()
    }
    
    private func sendWebSocketMessage(_ message: [String: Any]) {
        let data = try! JSONSerialization.data(withJSONObject: message, options: .prettyPrinted)
        let string = NSString(data: data, encoding: String.Encoding.utf8.rawValue)! as String
        print("sendWebSocketMessage: \(string)");
        webSocket!.send(string)
    }
}

extension ZinianWawajiController : SRWebSocketDelegate {
    func webSocketDidOpen(_ newWebSocket: SRWebSocket!) {
        webSocket = newWebSocket
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didFailWithError error: Error!) {
        connectWebSocket()
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didCloseWithCode code: Int, reason: String!, wasClean: Bool) {
        connectWebSocket()
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didReceiveMessage message: Any!) {
    }
}

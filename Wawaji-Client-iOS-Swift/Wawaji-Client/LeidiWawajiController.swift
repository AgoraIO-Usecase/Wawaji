//
//  LeidiWawajiController.swift
//  Wawaji-Client
//
//  Created by suleyu on 2017/12/11.
//  Copyright © 2017 Agora. All rights reserved.
//

import Foundation
import SocketRocket

class LeidiWawajiController: NSObject, WawajiController {
    static let webSocketUrl: String = <#Leidi Server Address#>
    
    let roomId : Int! = <#Leidi Room ID#>
    
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
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/start", "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
    }
    
    func startMoveUp() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/move/back", "data" : ["time" : 10000], "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func stopMoveUp() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/stop", "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func startMoveDown() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/move/front", "data" : ["time" : 10000], "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func stopMoveDown() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/stop", "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func startMoveLeft() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/move/left", "data" : ["time" : 10000], "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func stopMoveLeft() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/stop", "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func startMoveRight() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/move/right", "data" : ["time" : 10000], "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func stopMoveRight() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/stop", "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    func fetch() -> Bool {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/catch", "type" : "post", "id" : timeInterval]
        sendWebSocketMessage(messageDic)
        return true
    }
    
    private func connectWebSocket() {
        if let oldWebSocket = webSocket {
            oldWebSocket.close()
            oldWebSocket.delegate = nil
            webSocket = nil
        }
        
        let newWebSocket = SRWebSocket(url: URL(string: LeidiWawajiController.webSocketUrl))
        newWebSocket!.delegate = self
        newWebSocket!.open()
    }
    
    private func sendWebSocketMessage(_ message: [String: Any]) {
        let data = try! JSONSerialization.data(withJSONObject: message, options: .prettyPrinted)
        let string = NSString(data: data, encoding: String.Encoding.utf8.rawValue)! as String
        print("sendWebSocketMessage: \(string)");
        webSocket!.send(string)
    }
    
    private func sendEnterCommand() {
        let timeInterval : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["uri" : "/rooms/\(roomId!)/enter", "data" : ["token" : "no_token"], "type" : "post", "id" : timeInterval]
        _ = sendWebSocketMessage(messageDic)
    }
}

extension LeidiWawajiController : SRWebSocketDelegate {
    func webSocketDidOpen(_ newWebSocket: SRWebSocket!) {
        print("webSocketDidOpen")
        webSocket = newWebSocket
        sendEnterCommand()
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didFailWithError error: Error!) {
        print("webSocket:didFailWithError: \(error!)")
        connectWebSocket()
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didCloseWithCode code: Int, reason: String!, wasClean: Bool) {
        print("webSocket:didCloseWithCode: \(code), reason: \(reason!)")
        connectWebSocket()
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didReceiveMessage message: Any!) {
        print("webSocket:didReceiveMessage: \(message!)")
        
        let string = message as! String
        let data = string.data(using: .utf8)
        let decoded = try! JSONSerialization.jsonObject(with: data!, options: [])
        let dic = decoded as! [String : Any]
        if dic["id"] == nil {
            let type = dic["type"] as! String
            if type == "message" {
                let data = dic["data"] as! [String : Any]
                if let result = data["result"] as? Int {
                    if let fetchResult = fetchResult {
                        fetchResult(result == 1)
                    }
                }
            }
        }
    }
}

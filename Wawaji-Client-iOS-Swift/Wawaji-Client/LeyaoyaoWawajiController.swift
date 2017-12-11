//
//  LeyaoyaoWawajiController.swift
//  Wawaji-Client
//
//  Created by suleyu on 2017/12/1.
//  Copyright © 2017 Agora. All rights reserved.
//

import Foundation
import SocketRocket

class LeyaoyaoWawajiController: NSObject, WawajiController {
    static let leyaoyaoServer: String = "https://live.leyaoyao.com"
    static let leyaoyaoAppID: String = <#Your App ID from Leyaoyao#>
    
    let binding = "UserId"
    let roomId : Int! = <#Leyaoyao Room ID#> // you can get all available rooms by getRooms method
    
    var webSocket : SRWebSocket?
    var fetchResult : ((Bool) -> Void)?
    
    deinit {
        webSocket?.close()
        webSocket?.delegate = nil
        webSocket = nil
    }
    
    // MARK: - Public Methods
    
    func initialize() {
//        getRooms()
        createUser()
    }
    
    func insertCion() {
        getWebSocketUrl(roomId)
    }
    
    func startMoveUp() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "u"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    func stopMoveUp() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "W"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    func startMoveDown() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "d"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    func stopMoveDown() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "S"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    func startMoveLeft() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "l"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    func stopMoveLeft() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "A"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    func startMoveRight() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "r"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    func stopMoveRight() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "D"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    func fetch() -> Bool {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Control", "data" : ["direction" : "b"], "extra" : extra]
        return sendWebSocketMessage(messageDic)
    }
    
    // MARK: - HTTP Connection

    private func getRooms() {
        let url = URL(string: LeyaoyaoWawajiController.leyaoyaoServer + "/api/rooms?appId=" + LeyaoyaoWawajiController.leyaoyaoAppID)!
        var request = URLRequest(url: url, cachePolicy: .reloadIgnoringLocalAndRemoteCacheData, timeoutInterval: 10)
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.httpMethod = "GET"
        
        let dataTask = URLSession.shared.dataTask(with: request) { (data, response, error) in
            guard error == nil else {
                print("get rooms error : \(error!)")
                return
            }
            
            guard response != nil else {
                print("get rooms response is nil")
                return
            }
            
            let resp = response as! HTTPURLResponse
            guard resp.statusCode == 200 else {
                print("get rooms response code : \(resp.statusCode)")
                return
            }
            
            let jsonString = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)! as String
            print("get rooms return : \(jsonString)")
            
            let decoded = try! JSONSerialization.jsonObject(with: data!, options: [])
            let dic = decoded as! [String : Any]
            let result = dic["result"] as! Int
            if result == 0 {
                let data = dic["data"] as! [String : Any]
                let rooms = data["rooms"] as! [[String : Any]]
                for room in rooms {
                    let roomId = room["id"] as! Int
                    print("room id : \(roomId)")
                }
            }
        }
        dataTask.resume()
    }

    private func createUser() {
        let params = ["appId":LeyaoyaoWawajiController.leyaoyaoAppID, "binding":binding]
        let jsonData = try! JSONSerialization.data(withJSONObject: params, options: .prettyPrinted)
        
        let url = URL(string: LeyaoyaoWawajiController.leyaoyaoServer + "/api/users")!
        var request = URLRequest(url: url, cachePolicy: .reloadIgnoringLocalAndRemoteCacheData, timeoutInterval: 10)
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.httpBody = jsonData
        request.httpMethod = "POST"
        
        let dataTask = URLSession.shared.dataTask(with: request) { [weak self] (data, response, error) in
            guard error == nil else {
                print("create user error : \(error!)")
                return
            }
            
            guard response != nil else {
                print("create user response is nil")
                return
            }
            
            let resp = response as! HTTPURLResponse
            guard resp.statusCode == 200 else {
                print("create user response code : \(resp.statusCode)")
                return
            }
            
            let jsonString = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)! as String
            print("create user return : \(jsonString)")
            
            let decoded = try! JSONSerialization.jsonObject(with: data!, options: [])
            let dic = decoded as! [String : Any]
            let result = dic["result"] as! Int
            if result == 0 {
                let data = dic["data"] as! [String : Any]
                let user = data["user"] as! [String : Any]
                let account = user["account"] as! Int
                print("account : \(account)")
                
                // FIXME: auto charge, just for demo
                if (account < 10000) {
                    self?.charge(10000)
                }
            }
        }
        dataTask.resume()
    }
    
    private func charge(_ account: Int) {
        let params : [String : Any] = ["appId":LeyaoyaoWawajiController.leyaoyaoAppID, "binding":binding, "amount": account]
        let jsonData = try! JSONSerialization.data(withJSONObject: params, options: .prettyPrinted)
        
        let url = URL(string: LeyaoyaoWawajiController.leyaoyaoServer + "/api/charge")!
        var request = URLRequest(url: url, cachePolicy: .reloadIgnoringLocalAndRemoteCacheData, timeoutInterval: 10)
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.httpBody = jsonData
        request.httpMethod = "POST"
        
        let dataTask = URLSession.shared.dataTask(with: request) { (data, response, error) in
            guard error == nil else {
                print("charge error : \(error!)")
                return
            }
            
            guard response != nil else {
                print("charge response is nil")
                return
            }
            
            let resp = response as! HTTPURLResponse
            guard resp.statusCode == 200 else {
                print("charge response code : \(resp.statusCode)")
                return
            }
            
            let jsonString = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)! as String
            print("charge return : \(jsonString)")
            
            let decoded = try! JSONSerialization.jsonObject(with: data!, options: [])
            let dic = decoded as! [String : Any]
            let result = dic["result"] as! Int
            if result == 0 {
                print("charge success")
            }
            else {
                print("charge failed")
            }
        }
        dataTask.resume()
    }
    
    private func getWebSocketUrl(_ room: Int) {
        let url = URL(string: LeyaoyaoWawajiController.leyaoyaoServer + "/api/websocket_url?appId=\(LeyaoyaoWawajiController.leyaoyaoAppID)&binding=\(binding)&roomId=\(room)")!
        var request = URLRequest(url: url, cachePolicy: .reloadIgnoringLocalAndRemoteCacheData, timeoutInterval: 10)
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.httpMethod = "GET"
        
        let dataTask = URLSession.shared.dataTask(with: request) { [weak self] (data, response, error) in
            guard error == nil else {
                print("get websocket url error : \(error!)")
                return
            }
            
            guard response != nil else {
                print("get websocket url response is nil")
                return
            }
            
            let resp = response as! HTTPURLResponse
            guard resp.statusCode == 200 else {
                print("get websocket url response code : \(resp.statusCode)")
                return
            }
            
            let jsonString = NSString(data: data!, encoding: String.Encoding.utf8.rawValue)! as String
            print("get websocket url return : \(jsonString)")
            
            let decoded = try! JSONSerialization.jsonObject(with: data!, options: [])
            let dic = decoded as! [String : Any]
            let result = dic["result"] as! Int
            if result == 0 {
                let data = dic["data"] as! [String : Any]
                let webSocketUrl = data["wsUrl"] as! String
                print("get websocket url : \(webSocketUrl)")
                
                self?.connectWebSocket(webSocketUrl)
            }
        }
        dataTask.resume()
    }

    // MARK: - WebSocket

    private func connectWebSocket(_ urlString: String) {
        if let oldWebSocket = webSocket {
            oldWebSocket.close()
            oldWebSocket.delegate = nil
            webSocket = nil
        }

        let newWebSocket = SRWebSocket(url: URL(string: urlString))
        newWebSocket!.delegate = self
        newWebSocket!.open()
    }
    
    private func sendWebSocketMessage(_ message: [String: Any]) -> Bool {
        guard let webSocket = webSocket else {
            return false
        }
        
        let data = try! JSONSerialization.data(withJSONObject: message, options: .prettyPrinted)
        let string = NSString(data: data, encoding: String.Encoding.utf8.rawValue)! as String
        print("sendWebSocketMessage: \(string)");
        webSocket.send(string)
        return true
    }
    
    private func sendInsertCommand() {
        let extra : Int = Int(Date().timeIntervalSinceReferenceDate * 1000)
        let messageDic : [String : Any] = ["type" : "Insert", "data" : NSNull(), "extra" : extra]
        _ = sendWebSocketMessage(messageDic)
    }
}

extension LeyaoyaoWawajiController : SRWebSocketDelegate {
    func webSocketDidOpen(_ newWebSocket: SRWebSocket!) {
        print("webSocketDidOpen")
        webSocket = newWebSocket
        sendInsertCommand()
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didFailWithError error: Error!) {
        print("webSocket:didFailWithError: \(error!)")
        webSocket?.delegate = nil
        self.webSocket = nil
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didCloseWithCode code: Int, reason: String!, wasClean: Bool) {
        print("webSocket:didCloseWithCode: \(code), reason: \(reason!)")
        webSocket?.delegate = nil
        self.webSocket = nil
    }
    
    func webSocket(_ webSocket: SRWebSocket!, didReceiveMessage message: Any!) {
        print("webSocket:didReceiveMessage: \(message!)")
        
        let string = message as! String
        let data = string.data(using: .utf8)
        let decoded = try! JSONSerialization.jsonObject(with: data!, options: [])
        let dic = decoded as! [String : Any]
        let type = dic["type"] as! String
        if type == "Result" {
            webSocket.close()
            webSocket.delegate = nil
            self.webSocket = nil
            
            let result = dic["data"] as! Bool
            if let fetchResult = fetchResult {
                fetchResult(result)
            }
        }
    }
}

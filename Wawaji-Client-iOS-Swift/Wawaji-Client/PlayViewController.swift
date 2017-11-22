//
//  PlayViewController.swift
//  AgoraWawaji
//
//  Created by suleyu on 2017/11/22.
//  Copyright © 2017 Agora. All rights reserved.
//

import UIKit
import SocketRocket
import AgoraRtcEngineKit

class PlayViewController: UIViewController {
    static let WebSocketUrlString: String = <#Your Wawaji Controlling WebSocket Url#>
    
    public var player : Bool!
    public var channel : String!
    
    @IBOutlet weak var videoView: UIView!
    @IBOutlet weak var controlView: UIView!
    
    var webSocket : SRWebSocket?
    var mediaEngine : AgoraRtcEngineKit!
    var allStreamUids = [UInt]()
    var currentStreamUid : UInt = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationItem.title = channel
        // Do any additional setup after loading the view.
        
        if player {
            connectWebSocket()
        }
        else {
            controlView.removeFromSuperview()
        }
        
        loadMediaEngine();
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        UIApplication.shared.isIdleTimerDisabled = false
        mediaEngine.leaveChannel(nil)
        
        webSocket?.close()
        webSocket?.delegate = nil
        webSocket = nil
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func leave(_ sender: Any) {
        self.navigationController?.popViewController(animated: true)
    }
    
    @IBAction func switchCamera(_ sender: Any) {
        guard allStreamUids.count > 1 else {
            showAlert(NSLocalizedString("NoMoreCamera", comment: ""))
            return
        }
        
        let videoCanvas = AgoraRtcVideoCanvas()
        videoCanvas.uid = currentStreamUid;
        videoCanvas.view = nil;
        mediaEngine.setupRemoteVideo(videoCanvas)

        var index = allStreamUids.index(of: currentStreamUid)!
        if index == allStreamUids.count - 1 {
            index = 0
        }
        else {
            index += 1
        }
        currentStreamUid = allStreamUids[index]
        
        let newVideoCanvas = AgoraRtcVideoCanvas()
        newVideoCanvas.uid = currentStreamUid;
        newVideoCanvas.view = videoView;
        newVideoCanvas.renderMode = .render_Hidden;
        mediaEngine.setupRemoteVideo(newVideoCanvas)
    }
    
    @IBAction func cion(_ sender: Any) {
        let messageDic : [String : Any] = ["type" : "Insert", "data" : "", "extra" : 123456]
        sendWebSocketMessage(messageDic)
    }
    
    @IBAction func up(_ sender: Any) {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "u"]
        sendWebSocketMessage(messageDic)
    }
    
    @IBAction func down(_ sender: Any) {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "d"]
        sendWebSocketMessage(messageDic)
    }
    
    @IBAction func left(_ sender: Any) {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "l"]
        sendWebSocketMessage(messageDic)
    }
    
    @IBAction func right(_ sender: Any) {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "r"]
        sendWebSocketMessage(messageDic)
    }
    
    @IBAction func fetch(_ sender: Any) {
        let messageDic : [String : Any] = ["type" : "Control", "data" : "b"]
        sendWebSocketMessage(messageDic)
    }
    
    func connectWebSocket() {
        if let oldWebSocket = webSocket {
            oldWebSocket.delegate = nil
            webSocket = nil
        }
        
        let newWebSocket = SRWebSocket(url: URL(string: PlayViewController.WebSocketUrlString))
        newWebSocket!.delegate = self
        newWebSocket!.open()
    }
    
    func sendWebSocketMessage(_ message: [String: Any]) {
        let data = try! JSONSerialization.data(withJSONObject: message, options: .prettyPrinted)
        webSocket?.send(data)
    }
    
    func loadMediaEngine() {
        mediaEngine = AgoraRtcEngineKit.sharedEngine(withAppId: KeyCenter.appID, delegate: self)
        mediaEngine.setChannelProfile(.channelProfile_LiveBroadcasting);
        mediaEngine.setClientRole(.clientRole_Broadcaster, withKey: nil)
        mediaEngine.enableVideo();
        mediaEngine.enableLocalVideo(false);
        mediaEngine.enableAudio()
        mediaEngine.muteLocalAudioStream(true);
        mediaEngine.setParameters("{\"che.audio.external_capture\": true}");
        
        let result = mediaEngine.joinChannel(byKey: nil, channelName: channel, info: nil, uid: 0, joinSuccess: nil)
        if result == 0 {
            UIApplication.shared.isIdleTimerDisabled = true;
        }
        else {
            print("joinChannel failed: \(result)")
            showAlert(NSLocalizedString("JoinChannelFailed", comment: "")) {
                self.dismiss(animated: true, completion: nil)
            }
        }
    }
    
    func showAlert(_ message: String, completion: (() -> Swift.Void)? = nil) {
        let alertController = UIAlertController(title: nil, message: message, preferredStyle: .alert)
        let okAction = UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default) { action in
            if let completion = completion {
                completion()
            }
        }
        
        alertController.addAction(okAction)
        self.present(alertController, animated: true, completion: nil)
    }
}

extension PlayViewController : AgoraRtcEngineDelegate {
    func rtcEngine(_ engine: AgoraRtcEngineKit!, didOccurError errorCode: AgoraRtcErrorCode) {
        print("rtcEngine:didOccurError: \(errorCode)")
    }
    
    func rtcEngine(_ engine: AgoraRtcEngineKit!, didJoinChannel channel: String!, withUid uid: UInt, elapsed: Int) {
        print("rtcEngine:didJoinChannel: \(channel)")
        UIApplication.shared.isIdleTimerDisabled = true
    }
    
    func rtcEngine(_ engine: AgoraRtcEngineKit!, didJoinedOfUid uid: UInt, elapsed: Int) {
        print("rtcEngine:didJoinedOfUid: \(uid)")
    }
    
    func rtcEngine(_ engine: AgoraRtcEngineKit!, firstRemoteVideoDecodedOfUid uid: UInt, size: CGSize, elapsed: Int) {
        print("rtcEngine:firstRemoteVideoDecodedOfUid: \(uid)")
        if allStreamUids.contains(uid) {
            return
        }
        
        allStreamUids.append(uid)
        if currentStreamUid == 0 {
            currentStreamUid = uid
            
            let videoCanvas = AgoraRtcVideoCanvas()
            videoCanvas.uid = currentStreamUid;
            videoCanvas.view = videoView;
            videoCanvas.renderMode = .render_Hidden;
            mediaEngine.setupRemoteVideo(videoCanvas)
        }
    }
    
    func rtcEngine(_ engine: AgoraRtcEngineKit!, didOfflineOfUid uid: UInt, reason: AgoraRtcUserOfflineReason) {
        print("rtcEngine:didOfflineOfUid: \(uid)")
    }
}

extension PlayViewController : SRWebSocketDelegate {
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

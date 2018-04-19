# API 文档 V2.1

### AgoraCMH5SDK


##### AgoraCMH5SDK.createClient();

    ```javascript
    var client = AgoraCMH5SDK.createClient();
    ```

返回Client实例。

### Client

##### client.init(appid, channel, options, callback_Success, callback_Fail)

Client初始化。客户端会尝试建立两个摄像头的视频流连接，并且拉取主摄像头的视频流。

+ appid 项目的App ID
+ channel 频道名
+ options
    + key 如果项目开启了动态key功能，则必须填写。没有开启则不要填写。
    + uid1 主摄像头的uid
    + uid2 副摄像头的uid
+ callback_Success 初始化成功时的回调
+ callback_Error(err) 初始化失败时的回调

##### client.play(options, callback)

初始化播放器、播放画面。

+ options
    + canvas1 主摄像头的画布的id。
    + canvas2 副摄像头的画布id。
+ callback(err) 可选。


    ```javascript
    var client = AgoraCMH5SDK.createClient();
    client.init(appid, channel, {
        key: key,//对应的动态key，如果没有请不需要传null，直接不带这个参数即可，可选
        uid1: 1, //主摄像头的uid
        uid2: 2, //副摄像头的uid
    }, function(){
        client.play({
            canvas1: "js-player1",
            canvas2: "js-player2"
        });
    }, function(err){
        console.error(err);
    });
    ```


##### client.switchCamera(callback)

切换主、副摄像头

+ callback(err)

##### client.isUsingFrontCamera()

判断是否在使用主摄像头

返回：`true`/`false`

##### client.destroy()

断开服务连接，释放client对象
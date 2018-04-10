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
    + container 可选，播放器的container元素。如不填，则需要在init之后手动调用play()
+ callback_Success 可选
+ callback_Error(err) 可选


    ```javascript
    var client = AgoraCMH5SDK.createClient();
    client.init(appid, channel, {
        key: key,//对应的动态key，如果没有请不需要传null，直接不带这个参数即可，可选
        uid1: 1, //主摄像头的uid
        uid2: 2, //副摄像头的uid
        container: document.getElementById("wawaji-container") //播放器的容器元素
    });
    ```

##### client.play(options, callback)

初始化播放器、播放画面。
如在`client.init`时已经传入过container，则会自动播放，无需调用`client.play()`方法。
播放器默认会采用container的宽度。

+ options
    + container 播放器的容器div元素。
+ callback(err) 可选。

##### client.switchCamera(callback)

切换主、副摄像头

+ callback(err) 可选

##### client.isUsingFrontCamera()

判断是否在使用主摄像头

返回：`true`/`false`

##### client.destroy()

断开服务连接，释放client对象
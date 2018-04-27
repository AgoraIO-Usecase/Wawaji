# Wawaji streaming client for Web(H5)


### 更新日志
- 2018/04/09 - 使用H264和JSMPEG混合方案
- 2018/02/25 - 修复了部分bug
- 2018/01/09 - 更新了SDK，进一步优化了摄像头切换的速度，增加了前端稳定性

### 接入指南 v2.1

> + [接入指南 for v1.3](./接入指南-v1.3.md)
> + [接入指南 for v1.2（已废弃）](./接入指南-v1.2.md)
> + [接入指南 for v1.1（已废弃）](./接入指南-v1.1.md)


### v2.1

    2.1 版本会为iPhone6以上的系统及一部分Android高端机适配H264解码方案，可减小码率与延时。

    注：通过RTMP推流的视频发送端会存在兼容性问题，请手动强制选择mpeg模式：

        var client = AgoraCMH5SDK.createClient({mode: "mpeg"});

1. **引入h5的js sdk文件**

2. **在html文件中加入播放器**


    ```html
    <div>
        <canvas id="js-player1"></canvas>
        <canvas id="js-player2"></canvas>
    </div>
    ```

3. **在js中使用以下代码初始化并播放h5视频**


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

4. **切换摄像头**


    ```javascript
    client.switchCamera();
    ```

5. **销毁播放器**

    如果您的应用为多页面应用，则大多数时候不需要使用该方法。
    若您使用的是React等技术实现的单页面应用，在重复初始化播放器的时候，请先调用一下方法确认销毁之前的播放视频实例。


    ```javascript
    client.destroy();
    ```





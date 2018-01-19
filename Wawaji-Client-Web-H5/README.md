# Wawaji streaming client for Web(H5)

### 更新日志
2018/01/09 - 更新了SDK，进一步优化了摄像头切换的速度，增加了前端稳定性


- **v1.2还可以继续使用，但独立集成不会包含声网对网络和视频的优化，推荐使用v1.3的方法集成**

### v1.3
1. **引入h5的js sdk文件**
注意如果您之前有使用v1.2的方案或是自己有引入jsmpeg播放器，由于本sdk中已经包含了声网的修改版，请确认移除之前的jsmpeg库的引用，防止代码冲突

2. **在html文件中加入canvas代码**
```html
<div>
    <canvas id="jsmpeg-player"></canvas>
    <canvas id="jsmpeg-player2"></canvas>
</div>
```
记录一下您这边使用的canvas id留用，jsmpeg-player与jsmpeg-player2分别对应正副摄像头

3. **在js中使用一下代码初始化并播放h5视频**
```javascript
//创建client实例
var client = AgoraCMH5SDK.createClient();
初始化client
client.init(appid, channel, {
    //对应的动态key，如果没有请不需要传null，直接不带这个参数即可，可选
    key: key,
    //主摄像头uid，默认为1，可选
    uid1: uid1,
    //副摄像头uid，默认为2，可选
    uid2: uid2
}, function(){
    //初始化成功
    client.play({
        //canvas 1 id
        canvas1: "jsmpeg-player",
        //canvas 2 id
        canvas2: "jsmpeg-player2"
    }, function(){
        //视频开始播放的回调
        console.log("started playing..");
    });
})
```

4. **切换摄像头**
```javascrit
client.switchCamera();
```

5. **销毁播放器**
如果您的应用为多页面应用，则大多数时候不需要使用该方法，若您使用的是React等技术实现的单页面应用，在重复初始化播放器的时候，请先调用一下方法确认销毁之前的播放视频实例。
```javascript
client.destroy();
```

### v1.2 (已废弃)

1. **获取节点服务器域名**
```javascript
$.ajax({
    url: "https://h5cs-1.agoraio.cn:7668/geth5gw/jsonp",
    type: "POST",
    headers: {
        "Content-type": "application/json; charset=utf-8"
    },
    data: JSON.stringify({
        key: <your app id>,
        cname: <your channel name>
    })
})
```


返回结果为可用服务器域名列表数组，或者error，如果当前服务已过载
一般最适合你当前网段和负载的为第一个域名


2. **使用获得的节点地址发送machine请求**

基本与v1.1相同，需要使用步骤1获得的域名开启视频服务，或获得视频服务信息若已开启
```javascript
$.ajax({
    url: "https://" + <domain from step 1> + "/v1/machine",
    type: "POST",
    data: {
        appid: machine.appid,
        channel: machine.channel,
        key: key
        //可选，若你没有开启动态key则不需要传，开启的话需要传你自己后台计算的动态key
        uid1: 主摄像头uid
        //可选，若不传则默认为1，请确认这个uid与你推流的uid一致，不然无法看到视频流
        uid2: 副摄像头uid
        //可选，若不传则默认为2，请确认这个uid与你推流的uid一致，不然无法看到视频流
    }
})
```

3. **根据获取的信息播放视频**

在返回的视频流信息中会有属于你的appid与频道对应的主副摄像头地址，该地址可直接使用第三方播放器如jsmpeg播放，视频服务信息的数据结构可参阅api文档

https://github.com/AgoraIO/Wawaji/blob/rtc-only/Wawaji-Client-Web-H5/docs/api.html




### v1.1 (已废弃)

- [http://wawa1.agoraio.cn:4000/viewer.html](http://wawa1.agoraio.cn:4000/viewer.html)
- [http://wawa2.agoraio.cn:4000/viewer.html](http://wawa2.agoraio.cn:4000/viewer.html)

API 文档参见：
[docs/api.html](docs/api.html)

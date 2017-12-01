# Wawaji streaming client for Web(H5)

- **注意，本分支仅包含媒体部分，若需要全套娃娃机控制+媒体方案请查看其它分支**
- **为了安全，建议大家在正式环境中启用 [动态密钥鉴权](https://document.agora.io/cn/1.14/instruction/key.html) 机制**
- **H5方案的视频传输需要特殊的Agora转码SDK，该SDK并不包括在本开源库中，如需要请找声网BD或客户支持同事索取，可以拨打 400 632 6626，或加入官方Q群 12742516 提问。**

这个示例项目演示了如何在H5环境(移动端浏览器或微信内置浏览器)快速集成 Agora 视频，实现视频转码传输与播放。

在这个示例项目中包含了以下功能：

- Agora视频在H5环境的播放

## 运行示例程序
首先在 [Agora.io 注册](https://dashboard.agora.io/cn/signup/) 注册账号，并创建自己的测试项目，获取到 AppID。

确保机器安装了最新的nodejs，推荐版本：

```
$ node -v
v8.9.0
$ npm -v
5.5.1
```

在根目录运行setup.js脚本：

```
./setup.sh -i <your app id>
```


在server.js中可以根据需要的视频插件(Profile)把需要播放视频流的频道添加到中控系统中，例如：

```javascript
//create video only profiles
var test_profiles = [];
for (var i = 1; i <= 8; i++) {
    //we create 8 JSMpeg profiles, with channel name "wawaji<i>"
    test_profiles.push(new VideoProfile(StreamMethod.JSMPEG, "wawaji" + i));
}

var manager = new WawajiManager(unique("server_agora"), io);
for (var i = 0; i < test_profiles.length; i++) {
    //add profiles as machines to manager
    manager.machines.add(unique('machine_pressure_test' + i), test_profiles[i]);
}
```
  
  
*注意：项目预置的Profile需要对应的娃娃机才可以正常控制，若没有对应的娃娃机，也可以参考已有的插件撰写自己的插件*
  
  


将Agora转码SDK解压后重命名为**Agora_Recording_SDK_for_Linux_FULL**与server.js置于同一目录。

完成后运行
```
node server.js
```
启动方案



## 运行环境
- Linux, NodeJS v8.9.0或以上, Npm 5.1.1或以上

## 联系我们
- 完整的 API 文档见 [文档中心](https://docs.agora.io/cn/)
- 如果在集成中遇到问题, 你可以到 [开发者社区](https://dev.agora.io/cn/) 提问
- 如果有售前咨询问题, 可以拨打 400 632 6626，或加入官方Q群 12742516 提问
- 如果需要售后技术支持, 你可以在 [Agora Dashboard](https://dashboard.agora.io) 提交工单
- 如果发现了示例代码的 bug, 欢迎提交 [issue](https://github.com/AgoraIO/Wawaji/issues)

## 代码许可
The MIT License (MIT).

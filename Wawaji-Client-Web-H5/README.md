# Wawaji client for Web(H5)

- **注意，本娃娃机项目使用了第三方的娃娃机控制协议，开发者需要做些修改，适配自己的娃娃机控制协议**
- **为了安全，建议大家在正式环境中启用 [动态密钥鉴权](https://document.agora.io/cn/1.14/instruction/key.html) 机制**
- **H5方案已由本地部署的形式正式变为服务式，使用h5推流不再需要本地部署sdk，h5视频集成方法请参阅 https://github.com/AgoraIO/Wawaji/tree/rtc-only/Wawaji-Client-Web-H5**

这个示例项目演示了如何在H5环境(移动端浏览器或微信内置浏览器)快速集成 Agora 视频和信令 SDK，实现在线抓娃娃。

在这个示例项目中包含了以下功能：

- 房间/机器管理
- 上机和抓娃娃
- 排队
- 离开

## 运行示例程序
首先在 [Agora.io 注册](https://dashboard.agora.io/cn/signup/) 注册账号，并创建自己的测试项目，获取到 AppID。
项目中一共有2个vault_template.js文件，请按照里面的提示填好对应的内容后将文件重命名为vault.js

完成后安装node依赖
```shell
npm install
```

在server.js中可以根据需要的娃娃机插件(Profile)把需要管理的娃娃机添加到中控系统中，例如：

```javascript
var zhuazhua2_profile = new ZhuaZhuaProfile(StreamMethod.JSMPEG);
var leidi_profile = new LeiDiProfile(StreamMethod.JSMPEG);
var manager = new WawajiManager(unique("server_agora"), io);
manager.onStarted = function(){
    manager.machines.add(unique('machine_leidi'), leidi_profile);
    manager.machines.add(unique('machine_zhuazhua'), zhuazhua2_profile);
}
```
  
  
*注意：项目预置的Profile需要对应的娃娃机才可以正常控制，若没有对应的娃娃机，也可以参考已有的插件撰写自己的插件*

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

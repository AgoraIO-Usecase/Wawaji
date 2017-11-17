# Wawaji client for Web(WebRTC)

*Read this in other languages: [English](README.en.md)*

- **注意，本娃娃机项目使用了第三方的娃娃机控制协议，开发者需要做些修改，适配自己的娃娃机控制协议**
- **为了安全，建议大家在正式环境中启用 [动态密钥鉴权](https://document.agora.io/cn/1.14/instruction/key.html) 机制**

这个示例项目演示了如何快速集成 Agora 视频和信令 SDK，实现在线抓娃娃。

在这个示例项目中包含了以下功能：

- 进入娃娃机；
- 上机和抓娃娃；
- 离开

## 运行示例程序
首先在 [Agora.io 注册](https://dashboard.agora.io/cn/signup/) 注册账号，并创建自己的测试项目，获取到 AppID。将 AppID 填写进 "index.html"

```
var app_key = 'YOUR APP ID';
```
```
var sig_appid = "YOUR SIGNALLING APP ID";
var sig_appcertificate = "YOUR SIGNALING APP CERTIFICATE";
```

在本示例当中娃娃机的控制是使用第三方的基于 [WebSocket](https://en.wikipedia.org/wiki/WebSocket)，开发者需要根据自己的情况调整这部分代码，具体的控制协议格式也可能需要修改

```
socket_host: 'Your Wawaji Controlling Protocol Server',
```
```
url: 'Your Wawaji Controlling Protocol Server, Check room status',
```

## 运行环境
- 本地 Web 环境比如 [lite-server](https://www.npmjs.com/package/lite-server) 或者服务端环境

## 联系我们
- 完整的 API 文档见 [文档中心](https://docs.agora.io/cn/)
- 如果在集成中遇到问题, 你可以到 [开发者社区](https://dev.agora.io/cn/) 提问
- 如果有售前咨询问题, 可以拨打 400 632 6626，或加入官方Q群 12742516 提问
- 如果需要售后技术支持, 你可以在 [Agora Dashboard](https://dashboard.agora.io) 提交工单
- 如果发现了示例代码的 bug, 欢迎提交 [issue](https://github.com/AgoraIO/Wawaji/issues)

## 代码许可
The MIT License (MIT).

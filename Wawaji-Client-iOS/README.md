# Wawaji Client for iOS

这个示例项目演示了如何快速集成 Agora 视频和信令 SDK，实现在线抓娃娃。

在这个示例项目中包含了以下功能：

- 进入娃娃机；
- 上机和抓娃娃；
- 离开

## 运行示例程序
首先在 [Agora.io 注册](https://dashboard.agora.io/cn/signup/) 注册账号，并创建自己的测试项目，获取到 AppID。将 AppID 和 AppCertificate 填写进 KeyCenter.mm。

```
static NSString * const kAppID = @"Your App ID"
static NSString * const kAppCertificate = @"Your App Certificate";

```

然后在 [Agora.io SDK](https://www.agora.io/cn/download/)
下载 **视频通话 + 直播 SDK**，解压后将其中的 **libs/AgoraRtcEngineKit.framework** 复制到本目录。
下载 **信令SDK**，解压后将其中的 **framework/AgoraSignalKit.framework** 复制到本目录。

最后使用 XCode 打开 Wawaji-Client-iOS.xcworkspace，连接 iPhone／iPad 测试设备或模拟器，设置有效的开发者签名后即可运行。

## 运行环境
* XCode 9.0 +

## 联系我们

- 完整的 API 文档见 [文档中心](https://docs.agora.io/cn/)
- 如果在集成中遇到问题，你可以到 [开发者社区](https://dev.agora.io/cn/) 提问
- 如果有售前咨询问题，可以拨打 400 632 6626，或加入官方Q群 12742516 提问
- 如果需要售后技术支持，你可以在 [Agora Dashboard](https://dashboard.agora.io) 提交工单
- 如果发现了示例代码的 bug, 欢迎提交 [issue](https://github.com/AgoraIO/Wawaji/issues)

## 代码许可

The MIT License (MIT).

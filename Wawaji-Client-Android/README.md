# Wawaji client for Android

*Read this in other languages: [English](README.en.md)*

- **注意，本娃娃机项目使用了第三方的娃娃机控制协议，开发者需要做些修改，适配自己的娃娃机控制协议**
- **为了安全，建议大家在正式环境中启用 [动态密钥鉴权](https://document.agora.io/cn/1.14/instruction/key.html) 机制**

这个示例项目演示了如何快速集成 Agora 视频和信令 SDK，实现在线抓娃娃。

在这个示例项目中包含了以下功能：

- 进入娃娃机；
- 上机和抓娃娃；
- 离开

## 运行示例程序
首先在 [Agora.io 注册](https://dashboard.agora.io/cn/signup/) 注册账号，并创建自己的测试项目，获取到 AppID。将 AppID 填写进 "app/src/main/res/values/strings_config.xml"

```
<string name="agora_app_id"><#YOUR APP ID#></string>
```
```
<string name="agora_signalling_app_id"><#YOUR SIGNALLING APP ID#></string>
<string name="agora_signalling_app_certificate"><#YOUR SIGNALLING APP CERTIFICATE#></string>
```

[Agora.io SDK](https://www.agora.io/cn/download/) 下载 **视频通话 + 直播 SDK**，解压后将其中的 **libs** 文件夹下的 ***.jar** 复制到本项目的 **app/libs** 下，其中的 **libs** 文件夹下的 **arm64-v8a**/**x86**/**armeabi-v7a** 复制到本项目的 **app/src/main/libs** 下。

**Agora.io Signaling SDK** 在本项目中用来控制娃娃机端的摄像头多视角切换，开发者可以根据自己的情况选择性使用。对于 **信令 SDK**，同样的 **libs/signal** 当中的 ***.jar** 复制到本项目的 **app/libs** 下，其中的 **libs/signal** 文件夹下的 **arm64-v8a**/**x86**/**armeabi-v7a** 复制到本项目的 **app/src/main/libs** 下

在本示例当中娃娃机的控制是使用第三方的基于 [WebSocket](https://en.wikipedia.org/wiki/WebSocket)，开发者需要根据自己的情况调整这部分代码，具体的控制协议格式也可能需要修改

```
public static final String WAWAJI_SERVER_URL = "Your Wawaji Controlling Protocol Server";
```

最后用 Android Studio 打开该项目，连上设备，编译并运行。

也可以使用 `Gradle` 直接编译运行。

## 运行环境
- Android Studio 2.0 +
- 真实 Android 设备 (Nexus 5X 或者其它设备)
- 部分模拟器会存在功能缺失或者性能问题，所以推荐使用真机

## 联系我们
- 完整的 API 文档见 [文档中心](https://docs.agora.io/cn/)
- 如果在集成中遇到问题, 你可以到 [开发者社区](https://dev.agora.io/cn/) 提问
- 如果有售前咨询问题, 可以拨打 400 632 6626，或加入官方Q群 12742516 提问
- 如果需要售后技术支持, 你可以在 [Agora Dashboard](https://dashboard.agora.io) 提交工单
- 如果发现了示例代码的 bug, 欢迎提交 [issue](https://github.com/AgoraIO/Wawaji/issues)

## 代码许可
The MIT License (MIT).

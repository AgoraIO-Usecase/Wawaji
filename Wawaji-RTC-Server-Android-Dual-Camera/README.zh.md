# Wawaji Server for Android Dual Camera

*Read this in other languages: [English](README.md)*

- **为了安全，建议大家在正式环境中启用 [动态密钥鉴权](https://document.agora.io/cn/1.14/instruction/key.html) 机制**

这个示例项目演示了如何快速集成 Agora 视频 SDK，实现直播抓娃娃。

在这个示例项目中包含了以下功能：

- 不启用动态密钥鉴权；
- 进入直播间；
- 直播抓娃娃；
- 离开

##新增功能点
- 加入存储用户名，APPID， UID 功能，第一次进入后设置了对应的选项， 第二次进入可以直接进入直播间直播
- 如需修改对应的字段的值，可在进入直播间后返回到主界面修改对应的选项
- 旁路推流功能，可设置帧率码率分辨率及推流地址（APPID 需开通了旁路推流功能）
- 支持同时开两路摄像头的设备上可以同时推两路摄像头数据

## 运行示例程序
首先在 [Agora.io 注册](https://dashboard.agora.io/cn/signup/) 注册账号，并创建自己的测试项目，获取到 AppID。将 AppID 填写进 "app/src/main/res/values/strings_config.xml"

```
<string name="agora_app_id"><#YOUR APP ID#></string>
```

[Agora.io SDK](https://www.agora.io/cn/download/) 下载 **视频通话 SDK**，解压后将其中的 **libs** 文件夹下的 ***.jar** 复制到本项目的 **app/libs** 下，其中的 **libs** 文件夹下的 **arm64-v8a**/**x86**/**armeabi-v7a** 复制到本项目的 **app/src/main/libs** 下。

最后用 Android Studio 打开该项目，连上设备，编译并运行。

也可以使用 `Gradle` 直接编译运行。

## 运行环境
- Android Studio 2.0 +
- 真实娃娃机设备

## 联系我们
- 完整的 API 文档见 [文档中心](https://docs.agora.io/cn/)
- 如果在集成中遇到问题, 你可以到 [开发者社区](https://dev.agora.io/cn/) 提问
- 如果有售前咨询问题, 可以拨打 400 632 6626，或加入官方Q群 12742516 提问
- 如果需要售后技术支持, 你可以在 [Agora Dashboard](https://dashboard.agora.io) 提交工单
- 如果发现了示例代码的 bug, 欢迎提交 [issue](https://github.com/AgoraIO/Wawaji/issues)

## 代码许可
The MIT License (MIT).

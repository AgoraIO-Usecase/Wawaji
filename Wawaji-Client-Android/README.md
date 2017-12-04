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
首先在 [Agora.io 注册](https://dashboard.agora.io/cn/signup/) 注册账号，并创建自己的测试项目，获取到 AppID。然后选择测试项目里的编辑，App Certificate 点击启用，根据操作拿到App Certificate。
将 AppID  和App Certificate填写进 "app/src/main/res/values/strings_config.xml"

```
<string name="agora_app_id_leidi"><#LEIDI APP ID#></string>
<string name="agora_app_certificate_leidi"><#LEIDI APP CERTIFICATE#></string>
<string name="agora_app_id_leyaoyao"><#LEYAOYAO APP ID#></string>
<string name="agora_app_id_zhuazhua"><#ZHUAZHUA APP ID#></string>
<string name="agora_app_id_huizhi"><#HUIZHI APP ID#></string>

<string name="agora_app_id_signal"><#SIGNAL APP ID#></string>
<string name="agora_app_certificate_signal"<#SIGNAL APP CERTIFICATE#></string>
```

在本示例当中娃娃机的控制是基于 Agora Signal Sdk 做的。
```
public static final String WAWAJI_SERVER_URL = "Your Wawaji Controlling Protocol Server";
```

WawajiPlayerActivity文件中修改对应娃娃机的房间名,做不同的 APP ID 判断。
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

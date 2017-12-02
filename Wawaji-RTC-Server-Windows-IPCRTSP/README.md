# Wawaji server for Windows

*Read this in other languages: [English](README.en.md)*

- **为了安全，建议大家在正式环境中启用 [动态密钥鉴权](https://document.agora.io/cn/1.14/instruction/key.html) 机制**

这个示例项目演示了如何快速集成 Agora视频，实现在线抓娃娃的音视频采集服务端。

## 功能说明
- 1.通过APPID,AppCertificate获取ChannelKey，并通过秘钥joinchannel();
- 2.通过RTSP 获取到网络流，通过自采集的方式传递给SDK

## 集成编译说明
- 1.登录房间参数配置在EnterDlg.cpp文件中的InitCtrl() 部分修改
- 2.RTSP拉流地址在DeviceDlg.cpp的InitCtrl()中修改
- 3.最后用 Visual Studio 打开该项目，编译并运行。

## 执行说明
- 1.SDK环境1.14.2
- 2.需要将SDK中的dll文件拷贝到编译执行文件目录
- 3.确保音频录制设备，音频播放设备，摄像头设备驱动正常，否则可能出现error.
- 4.确保采集solution 和 IPC摄像头配置参数一直(分辨率)

## 运行环境
- 运行 Windows 的个人电脑或者工业主板

## 联系我们
- 完整的 API 文档见 [文档中心](https://docs.agora.io/cn/)
- 如果在集成中遇到问题, 你可以到 [开发者社区](https://dev.agora.io/cn/) 提问
- 如果有售前咨询问题, 可以拨打 400 632 6626，或加入官方Q群 12742516 提问
- 如果需要售后技术支持, 你可以在 [Agora Dashboard](https://dashboard.agora.io) 提交工单
- 如果发现了示例代码的 bug, 欢迎提交 [issue](https://github.com/AgoraIO/Wawaji/issues)

## 代码许可
The MIT License (MIT).

# Wawaji server for Windows

*Read this in other languages: [English](README.en.md)*

- **为了安全，建议大家在正式环境中启用 [动态密钥鉴权](https://document.agora.io/cn/1.14/instruction/key.html) 机制**

这个示例项目演示了如何快速集成 Agora 视频，实现在线抓娃娃的音视频采集服务端。

## 功能说明
- 1.不需要获取 Channel key 加入房间
- 2.用户自定义配置 App Id，Channel name，UID 以及推流地址
- 3.自定义摄像头采集参数
- 4.加入配置文件 wawaji.ini，用户只需要配置 AppId，ChannelName，LoginUid，LoginUid; 前提只有两个有效摄像头，只能启用两个进程
- 5.用户配置好参数后，进程自动分配摄像头，自动进入房间,当出现摄像头信息冲突的时候，会自动调整，但是如果用户强制选择相同摄像头，
那么出现不出图的情形
- 6.增加守护进程，主要包含以下几个功能：
- 开启自启动
- 定时自启动：用户需要初始界面配置以及重启时间点（24 小时制，精确到秒）
- 崩溃之后自动恢复(能够保存崩溃日志信息)
- 通过配置 videoPreview 参数来决定是否需要开启本地预览功能（不开启本地预览功能会降低消耗，对硬件要求更低）

## 集成编译说明
- 1.登录房间参数配置在 EnterDlg.cpp 文件中的 InitCtrl() 部分修改
- 2.推流参数在 DeviceDlg.cpp 的 InitCtrl() 中修改
- 3.最后用 Visual Studio 打开该项目，编译并运行。
- 3.自定义摄像头采集参数,提前为每个摄像头对应的进程分配摄像头.用户需要确保每个进程选择的摄像头不同相互占用.
- 4.加入配置文件 wawaji.ini，用户只需要配置 AppId，ChannelName，LoginUid，LoginUid;
- 5.用户配置好参数后，启动指定进程加载提前分配好的摄像头.
- 6.增加新的 INI 配置项:ResolutionIndex(VideoProfile 对应的索引号),ResolutionSave (是否保存当前选择的 videoProfile 参数)
- 7.增加新的 INI 配置项:RtmpSave(是否保存当前填写的推流参数)，RtmpWidth,RtmpHeight,RtmpFps,RtmpBitrate,RtmpUrl


## 执行说明
- 1.SDK 环境 2.0.0
- 2.需要将 SDK 中的 dll 文件拷贝到编译执行文件目录
- 3.确保音频录制设备，音频播放设备，摄像头设备驱动正常，否则可能出现 error.
- 4.用户尽量使用正常的关闭程序操作，不要使用杀进程的方式，不然配置文件会出现冲突
- 5.当发现程序执行异常的时候，多数是配置文件由于操作不当造成的，如果硬件环境没有问题，用户恢复配置文件为默认并加入 App Id 即可正常执行.

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

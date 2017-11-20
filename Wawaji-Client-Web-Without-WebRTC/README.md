# Wawaji client for Web(H5 but non-WebRTC supported)

对于支持 [WebRTC](https://webrtc.org/) 的浏览器环境，我们建议您使用 [Wawaji-Client-Web](https://github.com/AgoraIO/Wawaji/tree/master/Wawaji-Client-Web)

对于不支持 [WebRTC](https://webrtc.org/) 的浏览器环境(典型的微信浏览器)，如果您的产品需要支持，就需要按照如下的办法来实现，该方案需要一个特殊的 **录制 SDK**，可以找 sales@agora.io 或者拨打 400 632 6626，或加入官方Q群 12742516 提问索取

## 系统需求
* Linux
* Node.js

## 部署步骤
1. 将 `client/server` 部分代码部署到服务器上
2. 将一同提供的声网 **录制 SDK** 部署到服务器上后解压
3. 编辑 `server` 目录下的 `start_record.sh` 文件，修改以下部分的路径

`
echo {\"Recording_Dir\":\"{你的 `client` 目录 绝对路径}/public/${APP_ID}${CHANNEL_NAME}\"}
`
`
nohup {你的 录制 SDK 目录 绝对路径}/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}/cfg.json --appliteDir {你的 录制 SDK 目录 绝对路径}/bin/ --getVideoFrame 4 --captureInterval 0 --channelProfile 1 > /dev/null 2>&1 &
`

若你有使用 [动态密钥鉴权](https://document.agora.io/cn/1.14/instruction/key.html)，则需要增加一个参数 --channelKey {你的 Dynamic Key}

4. 修改完毕后进入 demo 目录，运行 `npm install` 安装依赖
5. 完成后运行 `npm start` 即可开始使用

## 使用方法
1. 用任一声网直播直播端开频道进行直播
2. 访问部署 `client` 的服务器端 3000 端口，在出现的网页中输入 appid 与频道名称
3. 点击 Record 按钮启动录制(可以反复启动, 脚本会自动关闭重复进程)
4. 点击 Connect 即可开始查看切图视频

## 常见问题
### 若 demo 不正常工作，请依次排查下列问题
* 查看 `server/public` 目录中是否有生成录制目录，该目录以 appid + 频道名称 命名
* 若目录有生成，请进入目录查看截图是否有持续不断地生成
* 若截图正常生成，请重启 Node.js 服务器并使用主页面重启录制服务再试

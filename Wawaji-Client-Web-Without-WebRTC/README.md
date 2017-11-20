# 系统需求
* linux
* nodejs

# 部署步骤
1. 将demo部分代码部署到服务器上
2. 将一起提供的声网录制SDK部署到服务器上后解压
3. 编辑demo目录下的start_record.sh文件， 修改以下部分的路径

echo {\"Recording_Dir\":\"{你的demo目录绝对路径}/public/${APP_ID}${CHANNEL_NAME}\"}

nohup {你的录制SDK目录路径}/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}/cfg.json --appliteDir {你的录制SDK目录路径}/bin/ --getVideoFrame 4 --captureInterval 0 --channelProfile 1 > /dev/null 2>&1 &

若你有使用动态key，则需要增加一个参数 --channelKey {你的动态key}

4. 修改完毕后进入demo目录，运行npm install安装依赖
5. 完成后运行npm install即可开始使用

# 使用方法
1. 访问任一声网直播频道开始直播
2. 访问部署demo的服务器端3000端口，在出现的网页中输入appid与频道名称
3. 点击Record按钮启动录制 (可以反复启动, 脚本会自动关闭重复进程)
4. 点击Connect即可开始查看切图视频

# 常见问题
## 若demo不正常工作，请依次排查下列问题
* 查看demo目录下的public目录中是否有生成录制目录，该目录以appid+频道名称命名
* 若目录有生成，请进入目录查看截图是否有持续不断地生成
* 若截图正常生成，请重启node服务器并使用主页面重启录制服务再试

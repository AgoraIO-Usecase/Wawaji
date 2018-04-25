#AgoraWawajiUI

*其他语言版本：[简体中文](README.zh.md)

This open source repository mainly implements the following functions:

-  Configuration interface has wizard function
- Multiple video sources can be displayed on the same screen
- Automatically join the room
- Front-end printing of currently managed dolly status, which can fix a variety of abnormal information

#Instructions
Currently this version only supports 1, 2 cameras, a room management, the program uses setVideoProfileEx to set the resolution, supports 3 different scenarios

- Landscape mode
-

	Do not check the exchange width and height, do not check the left 90 degree rotation

- Capture side screen, vertical screen on the viewer
-

	Check the exchange width and height, do not check the left side 90 degree rotation

- Collector vertical screen mode
-

	Do not check the exchange width and height, check the left 90 degree rotation

Users can choose different configurations according to the actual scene

#Compilation instructions
Vs2013, sdk currently only supports 2.0.2_v6room special edition.



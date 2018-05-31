# Wawaji Server for Android  Dual Camera

*Read this in other languages： [简体中文](README.md)*

- **For security, it is recommended that you use the dynamic key authentication (https://document.agora.io/cn/1.14/instruction/key.html) mechanism in the formal environment.**

This sample project demonstrates how to quickly integrate Agora video SDK to achieve live broadcast of dolls.。

The following features are included in this example project:

- dynamic key authentication is not enabled;
- into the live room;
- live to catch the doll;
- leave

##New functional points
- add the storage user name, APPID, UID function. After the first entry, the corresponding options are set up, and the second entry can directly enter the live broadcast.
- if you want to modify the value of the corresponding field, you can return to the main interface to change the corresponding options after entering the live room.
- bypass push function, frame rate, rate resolution and push flow address can be set up (APPID bypass bypass function is required).
- supporting two cameras at the same time can simultaneously push two cameras data on the device.

##Run example program
First register in [Agora.io (https://dashboard.agora.io/cn/signup/), and create your own test project to get AppID. Fill in AppID with "app/src/main/res/values/strings_config.xml".

```
<string name="agora_app_id"><#YOUR APP ID#></string>
```

[Agora.io SDK](https://www.agora.io/cn/download/) Download the * * * video call SDK**, and copy the ***.jar** under the **libs** folder into the **app/libs** of the project after unzip, and the **arm64-v8a**/**x86**/**armeabi-v7a** under the **libs** folder is copied to the **app/src/main/jniLibs** of the project.

Finally, open the project with Android Studio, connect to the device, compile and run it.

You can also use `Gradle` to compile and run directly.

## Developer Environment Requirements
- Android Studio 2.0 or above
- Real devices (Nexus 5X or other devices)
- Some simulators are function missing or have performance issue, so real device is the best choice

## Connect Us
- You can find full API document at [Document Center](https://docs.agora.io/en/)
- You can file bugs about this demo at [issue](https://github.com/AgoraIO/Agora-Android-Tutorial-1to1/issues)

## License
The MIT License (MIT).

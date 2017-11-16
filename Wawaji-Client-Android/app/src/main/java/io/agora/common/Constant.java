package io.agora.common;

import io.agora.rtc.RtcEngine;

public class Constant {

    public static final String MEDIA_SDK_VERSION;

    static {
        String sdk = "undefined";
        try {
            sdk = RtcEngine.getSdkVersion();
        } catch (Throwable e) {
        }
        MEDIA_SDK_VERSION = sdk;
    }

    public static final String WAWAJI_SERVER_URL = "YOUR Wawaji Controlling Protocol Server";

    public static final int Wawaji_Ctrl_START = 1;
    public static final int Wawaji_Ctrl_UP = 2;
    public static final int Wawaji_Ctrl_DOWN = 3;
    public static final int Wawaji_Ctrl_LEFT = 4;
    public static final int Wawaji_Ctrl_RIGHT = 5;
    public static final int Wawaji_Ctrl_CATCH = 6;
    public static final int Wawaji_Ctrl_SWITCH_CAM = 7;

    public static final int Wawaji_Msg_TIMEOUT = 1;
    public static final int Wawaji_Msg_RESULT = 2;
    public static final int Wawaji_Msg_FORCED_LOGOUT = 3;
}

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

    public static final String WAWAJI_SERVER_URL = "Your Wawaji Controlling Protocol Server";

    public static final String WAWAJI_CONTROL_CENTER = "wawaji_cc_server";

    public static final int Wawaji_Fetch_LIST = 1;

    public static final int Wawaji_Ctrl_START = 2;
    public static final int Wawaji_Ctrl_UP = 3;
    public static final int Wawaji_Ctrl_DOWN = 4;
    public static final int Wawaji_Ctrl_LEFT = 5;
    public static final int Wawaji_Ctrl_RIGHT = 6;
    public static final int Wawaji_Ctrl_CATCH = 7;

    public static final int Wawaji_Msg_TIMEOUT = 1;
    public static final int Wawaji_Msg_RESULT = 2;
    public static final int Wawaji_Msg_FORCED_LOGOUT = 3;

    public static final int APP_Wawaji_Fetch_LIST_RESULT = 1;
}

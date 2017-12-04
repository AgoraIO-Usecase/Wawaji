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

    public static String WAWAJI_SERVER_URL = "Your Wawaji Controlling Protocol Server";
    public static final String LEYAOYAO_SERVER_URL = "leyaoyao server url";
    public static final String LEYAOYAO_APP_ID     = "leyaoyao app id";
    public static final String LEYAOYAO_BINDING    = "leyaoyao binding";
    public static boolean BEFIRSTWAWAJI            = true;

    public static final int Wawaji_CAM_MAIN = 1;
    public static final int Wawaji_CAM_SECONDARY = 2;

    public static final int Wawaji_Ctrl_START = 1;
    public static final int Wawaji_Ctrl_UP = 2;
    public static final int Wawaji_Ctrl_UP_S = 3;
    public static final int Wawaji_Ctrl_DOWN = 4;
    public static final int Wawaji_Ctrl_DOWN_S = 5;
    public static final int Wawaji_Ctrl_LEFT = 6;
    public static final int Wawaji_Ctrl_LEFT_S = 7;
    public static final int Wawaji_Ctrl_RIGHT = 8;
    public static final int Wawaji_Ctrl_RIGHT_S = 9;
    public static final int Wawaji_Ctrl_CATCH = 10;
    public static final int Wawaji_Ctrl_CATCH_S = 11;

    public static final int Wawaji_Msg_TIMEOUT = 1;
    public static final int Wawaji_Msg_RESULT = 2;
    public static final int Wawaji_Msg_FORCED_LOGOUT = 3;
    public static final int Wawaji_Msg_STARTCATCH= 4;
}

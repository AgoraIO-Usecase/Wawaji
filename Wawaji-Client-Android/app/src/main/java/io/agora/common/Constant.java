package io.agora.common;

import io.agora.rtc.RtcEngine;

public class Constant {

    public static final String MEDIA_SDK_VERSION;

    public static final int Wawaji_CAM_MAIN = 1;
    public static final int Wawaji_CAM_SECONDARY = 2;
    public static  int Wawaji_BG_SOUND = 1;

    static {
        String sdk = "undefined";
        try {
            sdk = RtcEngine.getSdkVersion();
        } catch (Throwable e) {
        }
        MEDIA_SDK_VERSION = sdk;
    }
}

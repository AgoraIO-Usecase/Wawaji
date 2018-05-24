package io.agora.wawaji.utils;

import io.agora.rtc.Constants;

/**
 * Created by yt on 2017/12/18/018.
 */

public class Constant {
    public static final String CHANNEL_NAME = "channel_name";
    public static final String CHANNEL_APPID = "appid";

    public static final String CHANNEL_URL1 = "url1";
    public static final String CHANNEL_UID1 = "uid1";
    public static final String CHANNEL_URL_W1 = "url_w1";
    public static final String CHANNEL_URL_H1 = "url_h1";
    public static final String CHANNEL_URL_BITRATE1 = "url_bitrate1";
    public static final String CHANNEL_URL_FPS1 = "url_fps1";
    public static final String CHANNEL_URL_STATE1 = "url_state1";

    public static final String CHANNEL_URL2 = "url2";
    public static final String CHANNEL_UID2 = "uid2";
    public static final String CHANNEL_URL_W2 = "url_w2";
    public static final String CHANNEL_URL_H2 = "url_h2";
    public static final String CHANNEL_URL_BITRATE2 = "url_bitrate2";
    public static final String CHANNEL_URL_FPS2 = "url_fps2";
    public static final String CHANNEL_URL_STATE2 = "url_state2";

    public static final String PREF_PROPERTY_PROFILE_IDX = "pref_profile_index";
    public static int[] VIDEO_PROFILES = new int[]{
            Constants.VIDEO_PROFILE_360P,
            Constants.VIDEO_PROFILE_480P,
            Constants.VIDEO_PROFILE_720P};

    public static final int DEFAULT_PROFILE_IDX = 1; // default use 480P


}

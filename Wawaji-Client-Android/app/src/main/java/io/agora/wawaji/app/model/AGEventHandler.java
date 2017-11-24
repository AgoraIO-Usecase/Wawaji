package io.agora.wawaji.app.model;

public interface AGEventHandler {
    void onFirstRemoteVideoDecoded(int uid, int width, int height, int elapsed);

    void onJoinChannelSuccess(String channel, int uid, int elapsed);

    void onUserOffline(int uid, int reason);

    void onExtraInfo(int msg, Object... data);

    void onChannelJoined(String channelID);

    void onChannelAttrUpdated(String channelID, String name, String value, String type);

    void onMessageInstantReceive(String account, int uid, String msg);
}

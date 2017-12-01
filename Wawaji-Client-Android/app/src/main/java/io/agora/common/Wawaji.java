package io.agora.common;

import com.google.gson.annotations.SerializedName;

import java.io.Serializable;

public class Wawaji implements Serializable {
    @SerializedName("name")
    private String name;

    @SerializedName("status")
    private int status;

    @SerializedName("players")
    private WawajiPlayer[] players;

    @SerializedName("video_channel")
    private String video_channel;

    @SerializedName("video_host")
    private String video_host;

    @SerializedName("video_appid")
    private String video_appid;

    @SerializedName("video_rotation")
    private String video_rotation;

    @SerializedName("stream_method")
    private int stream_method;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public WawajiPlayer[] getPlayers() {
        return players;
    }

    public void setPlayers(WawajiPlayer[] players) {
        this.players = players;
    }

    public String getVideo_channel() {
        return video_channel;
    }

    public void setVideo_channel(String video_channel) {
        this.video_channel = video_channel;
    }

    public String getVideo_host() {
        return video_host;
    }

    public void setVideo_host(String video_host) {
        this.video_host = video_host;
    }

    public String getVideo_appid() {
        return video_appid;
    }

    public void setVideo_appid(String video_appid) {
        this.video_appid = video_appid;
    }

    public String getVideo_rotation() {
        return video_rotation;
    }

    public void setVideo_rotation(String video_rotation) {
        this.video_rotation = video_rotation;
    }

    public int getStream_method() {
        return stream_method;
    }

    public void setStream_method(int stream_method) {
        this.stream_method = stream_method;
    }
}

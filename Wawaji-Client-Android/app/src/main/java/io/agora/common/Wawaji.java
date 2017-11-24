package io.agora.common;

import com.google.gson.annotations.SerializedName;

import java.io.Serializable;

public class Wawaji implements Serializable{
    @SerializedName("name")
    private String name;

    @SerializedName("status")
    private int status;

    @SerializedName("players")
    private WawajiPlayer[] players;

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
}

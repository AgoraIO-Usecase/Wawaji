package io.agora.common;

import com.google.gson.annotations.SerializedName;

public class Wawaji {
    @SerializedName("name")
    private String name;

    @SerializedName("status")
    private int status;

    @SerializedName("players")
    private WawajiPlayer[] players;
}

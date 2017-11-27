package io.agora.common;

import com.google.gson.annotations.SerializedName;

import java.io.Serializable;

public class WawajiPlayer implements Serializable {
    @SerializedName("uid")
    private int uid;

    @SerializedName("account")
    private String account;
}

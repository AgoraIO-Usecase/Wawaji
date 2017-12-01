package io.agora.common;

import com.google.gson.annotations.SerializedName;

public class WawajiMsg {

    @SerializedName("type")
    private String type;

    @SerializedName("data")
    private Object data;

    @SerializedName("extra")
    private Object extra;
}

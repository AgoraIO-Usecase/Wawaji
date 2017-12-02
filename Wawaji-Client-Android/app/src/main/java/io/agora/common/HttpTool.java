package io.agora.common;

import java.io.IOException;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

/**
 * Created by yt on 2017/12/2.
 */

public class HttpTool {

    public static final MediaType JSON
            = MediaType.parse("application/json; charset=UTF-8");

    private static String get(OkHttpClient client, String url) throws IOException{
        Request request = new Request.Builder()
                .url(url)
                .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
    }

    private static String post(OkHttpClient client, String url, String json) throws IOException {
        RequestBody body = RequestBody.create(JSON, json);
        Request request = new Request.Builder()
                .url(url)
                .post(body)
                .build();
        Response response = client.newCall(request).execute();
        return response.body().string();
    }


    public static String postLeyaoyaoWawajiWS() throws IOException {
        OkHttpClient client = new OkHttpClient();
        String json = "{\"appId\":\"" + Constant.LEYAOYAO_APP_ID + "\",\"binding\":\""+ Constant.LEYAOYAO_BINDING+"\",\"}";

        return post(client, Constant.LEYAOYAO_SERVER_URL + "/api/users", json);
    }
    public static String postLeyaoyaoWawajiCharge(int amount) throws IOException {
        OkHttpClient client = new OkHttpClient();
        String json = "{\"appId\":\"" + Constant.LEYAOYAO_APP_ID + "\",\"binding\":\""+ Constant.LEYAOYAO_BINDING + ",\"amount\":" +amount+"}";

        return post(client, Constant.LEYAOYAO_SERVER_URL + "/api/charge", json);
    }
    public static String getLeyaoyaoWawajiRooms() throws IOException {
        OkHttpClient client = new OkHttpClient();

        return get(client, Constant.LEYAOYAO_SERVER_URL + "/api/rooms?appId="+Constant.LEYAOYAO_APP_ID);
    }

    public static String getLeyaoyaoWawajiWebsocket(int roomid ) throws IOException {
        OkHttpClient client = new OkHttpClient();

        return get(client, Constant.LEYAOYAO_SERVER_URL + "/api/websocket_url?appId="+Constant.LEYAOYAO_APP_ID
               +"&binding="+ Constant.LEYAOYAO_BINDING +"&roomId=" + roomid);
    }

}

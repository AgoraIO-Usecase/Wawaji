package io.agora.wawaji.utils;

import android.text.TextUtils;
import android.util.Log;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.net.URLEncoder;

public class AppUtil {


    private static final String DYNAMIC_KEY_SERVICE_URL_PREFIX = "http://recording.agorapremium.agora.io:9001";

    public static String getDynamicKeyForChannel(String channel, int uid, String appId, String appCertificate) {
        Log.d("AppUtil" ,"getDynamicKeyForChannel " + channel + " " + (uid & 0xFFFFFFFFFL) + " " + DYNAMIC_KEY_SERVICE_URL_PREFIX +
                " " +  " " + appId + " " + appCertificate);

        try {
            StringBuilder target = new StringBuilder(DYNAMIC_KEY_SERVICE_URL_PREFIX + "/agora/media/genDynamicKey5?uid=" + (uid & 0xFFFFFFFFFL) + "&channelname=" + URLEncoder.encode(channel, "UTF-8"));
            if (!TextUtils.isEmpty(appId)) {
                target.append("&key=").append(appId).append("&sign=").append(appCertificate);
            }
            URL url = new URL(target.toString());
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setConnectTimeout(5 * 1000);
            conn.setRequestMethod("GET");
            InputStream inStream = conn.getInputStream();
            byte[] data = readInputStream(inStream);
            String key = new String(data, "UTF-8");
            Log.d("AppUtil" ,"getDynamicKeyForChannel " + channel + " " + key + " " + (uid & 0xFFFFFFFFFL));
            return key;
        } catch (UnsupportedEncodingException | MalformedURLException | ProtocolException e) {
            Log.e("AppUtil" ,Log.getStackTraceString(e));
        } catch (IOException e) {
            Log.e("AppUtil" ,Log.getStackTraceString(e));
        }
        return null;
    }



    private static byte[] readInputStream(InputStream inStream) throws IOException {
        ByteArrayOutputStream outStream = new ByteArrayOutputStream();
        byte[] buffer = new byte[1024];
        int len;
        while ((len = inStream.read(buffer)) != -1) {
            outStream.write(buffer, 0, len);
        }
        byte[] data = outStream.toByteArray();
        outStream.close();
        inStream.close();
        return data;
    }

}

package io.agora.common;

import android.text.TextUtils;
import android.util.Log;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.net.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class TokenUtils {

    private final static Logger log = LoggerFactory.getLogger(TokenUtils.class);

    /**
     * Generate Token
     *
     * @param appID
     * @param certificate
     * @param account
     * @param expiredTime
     * @return
     */
    public static String calcToken(String appID, String certificate, String account, long expiredTime) {
        // Token = 1:appID:expiredTime:sign
        // Token = 1:appID:expiredTime:md5(account + vendorID + certificate + expiredTime)

        String sign = md5hex((account + appID + certificate + expiredTime).getBytes());
        return "1:" + appID + ":" + expiredTime + ":" + sign;

    }

    public static String md5hex(byte[] s) {
        MessageDigest messageDigest = null;
        try {
            messageDigest = MessageDigest.getInstance("MD5");
            messageDigest.update(s);
            return hexlify(messageDigest.digest());
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            return "";
        }
    }

    public static String hexlify(byte[] data) {
        char[] DIGITS_LOWER = {'0', '1', '2', '3', '4', '5',
                '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

        char[] DIGITS_UPPER = {'0', '1', '2', '3', '4', '5',
                '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

        char[] toDigits = DIGITS_LOWER;
        int l = data.length;
        char[] out = new char[l << 1];
        // two characters form the hex value.
        for (int i = 0, j = 0; i < l; i++) {
            out[j++] = toDigits[(0xF0 & data[i]) >>> 4];
            out[j++] = toDigits[0x0F & data[i]];
        }
        return String.valueOf(out);

    }

    private static final String DYNAMIC_KEY_SERVICE_URL_PREFIX = "http://recording.agorapremium.agora.io:9001";

    public static String getDynamicKeyForJoinChannel(String channel, int uid, String appId, String appCertificate) {
        log.debug("getDynamicKeyForChannel " + channel + " " + (uid & 0xFFFFFFFFFL) + " " + DYNAMIC_KEY_SERVICE_URL_PREFIX +
                " " + appId + " " + appCertificate);

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
            log.debug("getDynamicKeyForChannel " + channel + " " + key + " " + (uid & 0xFFFFFFFFFL));
            return key;
        } catch (UnsupportedEncodingException | MalformedURLException | ProtocolException e) {
            log.error(Log.getStackTraceString(e));
        } catch (IOException e) {
            log.error(Log.getStackTraceString(e));
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

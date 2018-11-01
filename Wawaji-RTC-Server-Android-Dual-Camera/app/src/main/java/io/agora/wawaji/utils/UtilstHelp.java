package io.agora.wawaji.utils;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

/**
 * Created by yt on 2018/5/23/023.
 */

public class UtilstHelp {


    public static boolean isNetworkAvailable(Context ctx) {
        ConnectivityManager conMan = (ConnectivityManager) ctx.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (conMan == null) {
            return false;
        }

        NetworkInfo mobileInfo = null;
        try {
            mobileInfo = conMan.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
        if (mobileInfo != null && mobileInfo.isConnectedOrConnecting()) {
            return true;
        }

        NetworkInfo wifiInfo = null;
        try {
            wifiInfo = conMan.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
        if (wifiInfo != null && wifiInfo.isConnectedOrConnecting()) {
            return true;
        }

        NetworkInfo activeInfo = null;
        try {
            activeInfo = conMan.getActiveNetworkInfo();
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
        if (activeInfo != null && activeInfo.isConnectedOrConnecting()) {
            return true;
        }

        return false;
    }

}

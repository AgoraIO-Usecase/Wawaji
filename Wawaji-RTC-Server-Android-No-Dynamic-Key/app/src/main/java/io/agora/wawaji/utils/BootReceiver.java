package io.agora.wawaji.utils;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import io.agora.wawaji.server.MainActivity;

/**
 * Created by yt on 2017/12/15/015.
 */

public class BootReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals("android.intent.action.BOOT_COMPLETED")) { // boot completed
            Intent intent2 = new Intent(context, MainActivity.class);
            intent2.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(intent2);
        }
    }
}

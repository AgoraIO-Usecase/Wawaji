package io.agora.wawaji.utils;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import io.agora.wawaji.server.FirstServer;
import io.agora.wawaji.server.MainActivity;

public class BootReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        if ("android.intent.action.BOOT_COMPLETED".equals(intent.getAction())) {
            Intent intent2 = new Intent(context, MainActivity.class);
            intent2.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(intent2);
        }
    }
}
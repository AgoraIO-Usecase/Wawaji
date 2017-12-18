package io.agora.wawaji.server;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import io.agora.wawaji.utils.WawajiCrashHandler;


public class MainActivity extends AppCompatActivity {
    private static final String LOG_TAG = MainActivity.class.getSimpleName();

    private static final int PERMISSION_REQ_ID_WRITE_EXTERNAL = 20;
    private String channelName = "";
    private String appid = "";
    private int uid = 0;
    private EditText textRoomName;
    private EditText textRoomAppid;
    private EditText textRoomUid;


    @Override
    public boolean navigateUpTo(Intent upIntent) {
        return super.navigateUpTo(upIntent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if (checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE, PERMISSION_REQ_ID_WRITE_EXTERNAL)) {
            WawajiCrashHandler crashHandler = WawajiCrashHandler.getInstance();
            crashHandler.init(getApplicationContext());
        }

        initUIandEvent();

    }


    protected void initUIandEvent() {
        textRoomName = (EditText) findViewById(R.id.room_name);
        textRoomName.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                boolean isEmpty = s.toString().isEmpty();
                findViewById(R.id.button_join).setEnabled(!isEmpty);
            }
        });

        textRoomAppid = (EditText) findViewById(R.id.room_appid);
        textRoomUid = (EditText) findViewById(R.id.room_uid);

        channelName = WawajiApplication.the().getSetting("channelname", "");
        appid = WawajiApplication.the().getSetting("appid", "");
        uid = WawajiApplication.the().getSetting("uid", 0);

        if (!channelName.equals("")) {
            textRoomName.setText(channelName);

            if (!appid.equals("")) {
                textRoomAppid.setText(appid);
            }

            if (uid != 0) {
                textRoomUid.setText(uid);
            }

            startActivity();
        }

    }

    public boolean checkSelfPermission(String permission, int requestCode) {
        Log.i(LOG_TAG, "checkSelfPermission " + permission + " " + requestCode);
        if (ContextCompat.checkSelfPermission(this,
                permission)
                != PackageManager.PERMISSION_GRANTED) {

            ActivityCompat.requestPermissions(this,
                    new String[]{permission},
                    requestCode);
            return false;
        }
        return true;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,
                                           @NonNull String permissions[], @NonNull int[] grantResults) {
        Log.i(LOG_TAG, "onRequestPermissionsResult " + grantResults[0] + " " + requestCode);

        switch (requestCode) {
            case PERMISSION_REQ_ID_WRITE_EXTERNAL: {
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    WawajiCrashHandler crashHandler = WawajiCrashHandler.getInstance();
                    crashHandler.init(getApplicationContext());
                }
                break;
            }

        }
    }

    public void onClickJoin(View view) {

        channelName = textRoomName.getText().toString();
        appid = textRoomAppid.getText().toString();

        if (!textRoomUid.getText().toString().isEmpty()) {
            uid = Integer.parseInt(textRoomUid.getText().toString());
        }

        WawajiApplication.the().setSetting("channelname", channelName);
        WawajiApplication.the().setSetting("appid", appid);
        WawajiApplication.the().setSetting("uid", uid);

        startActivity();

    }

    private void startActivity() {
        Intent i = new Intent(MainActivity.this, WawajiServerActivity.class);
        i.putExtra("channelname", channelName);
        i.putExtra("appid", appid);
        i.putExtra("uid", uid);
        startActivity(i);
    }

}

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
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.Toast;

import io.agora.wawaji.utils.Constant;
import io.agora.wawaji.utils.WawajiCrashHandler;


public class MainActivity extends AppCompatActivity {
    private static final String LOG_TAG = MainActivity.class.getSimpleName();

    private static final int PERMISSION_REQ_ID_WRITE_EXTERNAL = 20;
    private String channelName = "";
    private String appid = "";
    private int uid = 0;

    private String rtmpUrl = "";
    private int width = 0;
    private int height = 0;
    private int bitrate = 0;
    private int fps = 0;
    private boolean openRtmpStream = false;
    private boolean useCaptureFormatNV21 = false;

    private EditText textRoomName;
    private EditText textRoomAppid;
    private EditText textRoomUid;
    private EditText textRoomUrl;
    private EditText textWidth;
    private EditText textHeight;
    private EditText textBitrate;
    private EditText textFps;
    private CheckBox checkBoxPushFlow;
    private CheckBox checkBoxSetNv21;
    private RelativeLayout layoutRtmp;


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
        textRoomUrl = (EditText) findViewById(R.id.room_url_edit);
        textWidth = (EditText) findViewById(R.id.room_url_width);
        textHeight = (EditText) findViewById(R.id.room_url_height);
        textBitrate = (EditText) findViewById(R.id.room_url_bitrate);
        textFps = (EditText) findViewById(R.id.room_url_fps);
        layoutRtmp = (RelativeLayout) findViewById(R.id.room_layout_rtmp);
        checkBoxPushFlow = (CheckBox) findViewById(R.id.room_push_flow);
        checkBoxSetNv21= (CheckBox) findViewById(R.id.room_check_nv21);
        checkBoxPushFlow.setOnCheckedChangeListener(onCheckedChangeListener);
        checkBoxSetNv21.setOnCheckedChangeListener(onCheckedChangeListener);

        channelName = WawajiApplication.the().getSetting(Constant.CHANNEL_NAME, "");
        appid = WawajiApplication.the().getSetting(Constant.CHANNEL_APPID, "");
        uid = WawajiApplication.the().getSetting(Constant.CHANNEL_UID, 0);
        rtmpUrl = WawajiApplication.the().getSetting(Constant.CHANNEL_URL, "");
        width = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_W, 0);
        height = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_H, 0);
        bitrate = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_BITRATE, 0);
        fps = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_FPS, 0);
        openRtmpStream = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_STATE, false);
        useCaptureFormatNV21 = WawajiApplication.the().getSetting(Constant.CHANNEL_SET_NV21, false);

        if (!channelName.equals("")) {
            textRoomName.setText(channelName);

            if (!appid.equals("")) {
                textRoomAppid.setText(appid);
            }

            if (uid != 0) {
                textRoomUid.setText("" + uid);
            }
            if (!rtmpUrl.equals("")) {
                textRoomUrl.setText(rtmpUrl);
            }
            if (width != 0) {
                textWidth.setText("" + width);
            }
            if (height != 0) {
                textHeight.setText("" + height);
            }
            if (bitrate != 0) {
                textBitrate.setText("" + bitrate);
            }
            if (fps != 0) {
                textFps.setText("" + fps);
            }

            checkBoxPushFlow.setChecked(openRtmpStream);
            checkBoxSetNv21.setChecked(useCaptureFormatNV21);

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
        rtmpUrl = textRoomUrl.getText().toString();

        if (!textRoomUid.getText().toString().isEmpty()) {
            uid = Integer.parseInt(textRoomUid.getText().toString());
        }

        if (!textWidth.getText().toString().isEmpty()) {
            width = Integer.parseInt(textWidth.getText().toString());
        }
        if (!textHeight.getText().toString().isEmpty()) {
            height = Integer.parseInt(textHeight.getText().toString());
        }
        if (!textBitrate.getText().toString().isEmpty()) {
            bitrate = Integer.parseInt(textBitrate.getText().toString());
        }
        if (!textFps.getText().toString().isEmpty()) {
            fps = Integer.parseInt(textFps.getText().toString());
        }

        WawajiApplication.the().setSetting(Constant.CHANNEL_NAME, channelName);
        WawajiApplication.the().setSetting(Constant.CHANNEL_APPID, appid);
        WawajiApplication.the().setSetting(Constant.CHANNEL_UID, uid);
        WawajiApplication.the().setSetting(Constant.CHANNEL_SET_NV21, useCaptureFormatNV21);
        WawajiApplication.the().setSetting(Constant.CHANNEL_URL_STATE, openRtmpStream);

        if (openRtmpStream) {
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL, rtmpUrl);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_W, width);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_H, height);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_BITRATE, bitrate);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_FPS, fps);
        }

        startActivity();

    }

    private void startActivity() {
        Intent i = new Intent(MainActivity.this, WawajiServerActivity.class);
        i.putExtra(Constant.CHANNEL_NAME, channelName);
        i.putExtra(Constant.CHANNEL_APPID, appid);
        i.putExtra(Constant.CHANNEL_UID, uid);
        i.putExtra(Constant.CHANNEL_URL_STATE, openRtmpStream);
        i.putExtra(Constant.CHANNEL_SET_NV21, useCaptureFormatNV21);

        if (openRtmpStream) {
            i.putExtra(Constant.CHANNEL_URL, rtmpUrl);
            i.putExtra(Constant.CHANNEL_URL_W, width);
            i.putExtra(Constant.CHANNEL_URL_H, height);
            i.putExtra(Constant.CHANNEL_URL_BITRATE, bitrate);
            i.putExtra(Constant.CHANNEL_URL_FPS, fps);
        }

        if (appid.equals("") && getString(R.string.agora_app_id).equals("")){
            Toast.makeText(this, "No AppId can use", Toast.LENGTH_SHORT).show();
            return;
        }

        startActivity(i);
    }

    private CompoundButton.OnCheckedChangeListener onCheckedChangeListener = new CompoundButton.OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

            switch (buttonView.getId()){
                case R.id.room_push_flow:
                    openRtmpStream = isChecked;

                    if (isChecked) {
                        layoutRtmp.setVisibility(View.VISIBLE);
                    } else {
                        layoutRtmp.setVisibility(View.GONE);
                    }
                    break;
                case R.id.room_check_nv21:

                    useCaptureFormatNV21 = isChecked;
                    break;
            }


        }
    };


}

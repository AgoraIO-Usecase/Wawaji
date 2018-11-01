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
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.LineNumberReader;

import io.agora.wawaji.utils.Constant;
import io.agora.wawaji.utils.UtilstHelp;


public class MainActivity extends AppCompatActivity {
    private static final String LOG_TAG = MainActivity.class.getSimpleName();

    private static final int PERMISSION_REQ_ID_WRITE_EXTERNAL = 20;
    private String channelName = "";
    private String appid = "";

    private String rtmpUrl1 = "";
    private int uid1 = 0;
    private int width1 = 0;
    private int height1 = 0;
    private int bitrate1 = 0;
    private int fps1 = 0;
    private boolean openRtmpStream1 = false;

    private String rtmpUrl2 = "";
    private int uid2 = 0;
    private int width2 = 0;
    private int height2 = 0;
    private int bitrate2 = 0;
    private int fps2 = 0;
    private boolean openRtmpStream2 = false;

    private EditText textRoomName;
    private EditText textRoomAppid;

    private EditText textRoomUid1;
    private EditText textRoomUrl1;
    private EditText textWidth1;
    private EditText textHeight1;
    private EditText textBitrate1;
    private EditText textFps1;
    private CheckBox checkBoxPushFlow1;
    private RelativeLayout layoutRtmp1;

    private EditText textRoomUid2;
    private EditText textRoomUrl2;
    private EditText textWidth2;
    private EditText textHeight2;
    private EditText textBitrate2;
    private EditText textFps2;
    private CheckBox checkBoxPushFlow2;
    private RelativeLayout layoutRtmp2;

    @Override
    public boolean navigateUpTo(Intent upIntent) {
        return super.navigateUpTo(upIntent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE, PERMISSION_REQ_ID_WRITE_EXTERNAL)) {

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

        textRoomUid1 = (EditText) findViewById(R.id.room_uid1);
        textRoomUrl1 = (EditText) findViewById(R.id.room_url_edit1);
        textWidth1 = (EditText) findViewById(R.id.room_url_width1);
        textHeight1 = (EditText) findViewById(R.id.room_url_height1);
        textBitrate1 = (EditText) findViewById(R.id.room_url_bitrate1);
        textFps1 = (EditText) findViewById(R.id.room_url_fps1);
        layoutRtmp1 = (RelativeLayout) findViewById(R.id.room_layout_rtmp1);
        checkBoxPushFlow1 = (CheckBox) findViewById(R.id.room_push_flow1);
        checkBoxPushFlow1.setOnCheckedChangeListener(onCheckedChangeListener);

        textRoomUid2 = (EditText) findViewById(R.id.room_uid2);
        textRoomUrl2 = (EditText) findViewById(R.id.room_url_edit2);
        textWidth2 = (EditText) findViewById(R.id.room_url_width2);
        textHeight2 = (EditText) findViewById(R.id.room_url_height2);
        textBitrate2 = (EditText) findViewById(R.id.room_url_bitrate2);
        textFps2 = (EditText) findViewById(R.id.room_url_fps2);
        layoutRtmp2 = (RelativeLayout) findViewById(R.id.room_layout_rtmp2);
        checkBoxPushFlow2 = (CheckBox) findViewById(R.id.room_push_flow2);
        checkBoxPushFlow2.setOnCheckedChangeListener(onCheckedChangeListener);


        channelName = WawajiApplication.the().getSetting(Constant.CHANNEL_NAME, "wwjtest");
        appid = WawajiApplication.the().getSetting(Constant.CHANNEL_APPID, "");

        rtmpUrl1 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL1, "");
        uid1 = WawajiApplication.the().getSetting(Constant.CHANNEL_UID1, 1);
        width1 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_W1, 0);
        height1 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_H1, 0);
        bitrate1 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_BITRATE1, 0);
        fps1 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_FPS1, 0);
        openRtmpStream1 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_STATE1, false);

        rtmpUrl2 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL2, "");
        uid2 = WawajiApplication.the().getSetting(Constant.CHANNEL_UID2, 2);
        width2 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_W2, 0);
        height2 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_H2, 0);
        bitrate2 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_BITRATE2, 0);
        fps2 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_FPS2, 0);
        openRtmpStream2 = WawajiApplication.the().getSetting(Constant.CHANNEL_URL_STATE2, false);


        if (channelName != null) {
            textRoomName.setText(channelName);

            if (!appid.equals("")) {
                textRoomAppid.setText(appid);
            }

            if (uid1 != 0) {
                textRoomUid1.setText("" + uid1);
            }

            if (!rtmpUrl1.equals("") && !rtmpUrl1.equals("rtmp://")) {
                textRoomUrl1.setText(rtmpUrl1);
            }
            if (width1 != 0) {
                textWidth1.setText("" + width1);
            }
            if (height1 != 0) {
                textHeight1.setText("" + height1);
            }
            if (bitrate1 != 0) {
                textBitrate1.setText("" + bitrate1);
            }
            if (fps1 != 0) {
                textFps1.setText("" + fps1);
            }
            checkBoxPushFlow1.setChecked(openRtmpStream1);


            if (uid2 != 0) {
                textRoomUid2.setText("" + uid2);
            }
            if (!rtmpUrl2.equals("") && !rtmpUrl2.equals("rtmp://")) {
                textRoomUrl2.setText(rtmpUrl2);
            }
            if (width2 != 0) {
                textWidth2.setText("" + width2);
            }
            if (height2 != 0) {
                textHeight2.setText("" + height2);
            }
            if (bitrate2 != 0) {
                textBitrate2.setText("" + bitrate2);
            }
            if (fps2 != 0) {
                textFps2.setText("" + fps2);
            }
            checkBoxPushFlow2.setChecked(openRtmpStream2);

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
                }
                break;
            }

        }
    }

    public void onClickJoin(View view) {

        channelName = textRoomName.getText().toString();
        appid = textRoomAppid.getText().toString();
        rtmpUrl1 = textRoomUrl1.getText().toString();

        rtmpUrl2 = textRoomUrl2.getText().toString();

        if (!textRoomUid1.getText().toString().isEmpty()) {
            uid1 = Integer.parseInt(textRoomUid1.getText().toString());
        }
        if (!textWidth1.getText().toString().isEmpty()) {
            width1 = Integer.parseInt(textWidth1.getText().toString());
        }
        if (!textHeight1.getText().toString().isEmpty()) {
            height1 = Integer.parseInt(textHeight1.getText().toString());
        }
        if (!textBitrate1.getText().toString().isEmpty()) {
            bitrate1 = Integer.parseInt(textBitrate1.getText().toString());
        }
        if (!textFps1.getText().toString().isEmpty()) {
            fps1 = Integer.parseInt(textFps1.getText().toString());
        }


        if (!textRoomUid2.getText().toString().isEmpty()) {
            uid2 = Integer.parseInt(textRoomUid2.getText().toString());
        }
        if (!textWidth2.getText().toString().isEmpty()) {
            width2 = Integer.parseInt(textWidth2.getText().toString());
        }
        if (!textHeight2.getText().toString().isEmpty()) {
            height2 = Integer.parseInt(textHeight2.getText().toString());
        }
        if (!textBitrate2.getText().toString().isEmpty()) {
            bitrate2 = Integer.parseInt(textBitrate2.getText().toString());
        }
        if (!textFps2.getText().toString().isEmpty()) {
            fps2 = Integer.parseInt(textFps2.getText().toString());
        }

        WawajiApplication.the().setSetting(Constant.CHANNEL_NAME, channelName);
        WawajiApplication.the().setSetting(Constant.CHANNEL_APPID, appid);

        WawajiApplication.the().setSetting(Constant.CHANNEL_UID1, uid1);
        WawajiApplication.the().setSetting(Constant.CHANNEL_UID2, uid2);
        WawajiApplication.the().setSetting(Constant.CHANNEL_URL_STATE1, openRtmpStream1);
        WawajiApplication.the().setSetting(Constant.CHANNEL_URL_STATE2, openRtmpStream2);

        if (openRtmpStream1) {

            if (width1 == 0 || height1 == 0) {
                width1 = 640;
                height1 = 360;
            }
            if (bitrate1 == 0) {
                bitrate1 = 500;
            }
            if (fps1 == 0) {
                fps1 = 15;
            }


            WawajiApplication.the().setSetting(Constant.CHANNEL_URL1, rtmpUrl1);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_W1, width1);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_H1, height1);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_BITRATE1, bitrate1);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_FPS1, fps1);

        }
        if (openRtmpStream2) {

            if (width2 == 0 || height2 == 0) {
                width2 = 640;
                height2 = 360;
            }
            if (bitrate2 == 0) {
                bitrate2 = 500;
            }
            if (fps2 == 0) {
                fps2 = 15;
            }

            WawajiApplication.the().setSetting(Constant.CHANNEL_URL2, rtmpUrl2);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_W2, width2);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_H2, height2);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_BITRATE2, bitrate2);
            WawajiApplication.the().setSetting(Constant.CHANNEL_URL_FPS2, fps2);
        }

        startActivity();

    }

    private void startActivity() {
        if (!UtilstHelp.isNetworkAvailable(this)) {
            Toast.makeText(this, R.string.no_network, Toast.LENGTH_LONG).show();
            return;
        }

        Intent i = new Intent(MainActivity.this, FirstServer.class);
        i.putExtra(Constant.CHANNEL_NAME, channelName);
        i.putExtra(Constant.CHANNEL_APPID, appid);

        i.putExtra(Constant.CHANNEL_UID1, uid1);
        i.putExtra(Constant.CHANNEL_UID2, uid2);
        i.putExtra(Constant.CHANNEL_URL_STATE1, openRtmpStream1);
        i.putExtra(Constant.CHANNEL_URL_STATE2, openRtmpStream2);


        if (openRtmpStream1) {
            i.putExtra(Constant.CHANNEL_URL1, rtmpUrl1);

            i.putExtra(Constant.CHANNEL_URL_W1, width1);
            i.putExtra(Constant.CHANNEL_URL_H1, height1);
            i.putExtra(Constant.CHANNEL_URL_BITRATE1, bitrate1);
            i.putExtra(Constant.CHANNEL_URL_FPS1, fps1);
        }

        if (openRtmpStream2) {
            i.putExtra(Constant.CHANNEL_URL2, rtmpUrl2);
            i.putExtra(Constant.CHANNEL_URL_W2, width2);
            i.putExtra(Constant.CHANNEL_URL_H2, height2);
            i.putExtra(Constant.CHANNEL_URL_BITRATE2, bitrate2);
            i.putExtra(Constant.CHANNEL_URL_FPS2, fps2);
        }

        if (appid.equals("") && getString(R.string.agora_app_id).equals("")) {
            Toast.makeText(this, "No AppId can use", Toast.LENGTH_SHORT).show();
            return;
        }

        startActivity(i);
    }

    private CompoundButton.OnCheckedChangeListener onCheckedChangeListener = new CompoundButton.OnCheckedChangeListener() {
        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

            switch (buttonView.getId()) {
                case R.id.room_push_flow1:
                    openRtmpStream1 = isChecked;

                    if (isChecked) {
                        layoutRtmp1.setVisibility(View.VISIBLE);
                    } else {
                        layoutRtmp1.setVisibility(View.GONE);
                    }
                    break;
                case R.id.room_push_flow2:
                    openRtmpStream2 = isChecked;

                    if (isChecked) {
                        layoutRtmp2.setVisibility(View.VISIBLE);
                    } else {
                        layoutRtmp2.setVisibility(View.GONE);
                    }
                    break;

            }


        }
    };


    @Override
    public boolean onCreateOptionsMenu(final Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle presses on the action bar items
        switch (item.getItemId()) {
            case R.id.action_settings:
                forwardToSettings();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    public void forwardToSettings() {
        Intent i = new Intent(this, SettingsActivity.class);
        startActivity(i);
    }


}

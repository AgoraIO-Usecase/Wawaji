package io.agora.wawaji.server;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.SurfaceView;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;
import android.widget.Toast;

import io.agora.rtc.Constants;
import io.agora.rtc.IRtcEngineEventHandler;
import io.agora.rtc.PublisherConfiguration;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;
import io.agora.wawaji.utils.Constant;


public class WawajiServerActivity extends Activity {

    private static final String LOG_TAG = WawajiServerActivity.class.getSimpleName();

    private static final int PERMISSION_REQ_ID_RECORD_AUDIO = 22;
    private static final int PERMISSION_REQ_ID_CAMERA = PERMISSION_REQ_ID_RECORD_AUDIO + 1;

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

    private RtcEngine mRtcEngine; // Step 1
    private final IRtcEngineEventHandler mRtcEventHandler = new IRtcEngineEventHandler() { // Step 1

        @Override
        public void onJoinChannelSuccess(String channel, int uid, int elapsed) {
            Log.i(LOG_TAG, "onJoinChannelSuccess " + channel + " " + uid);
            super.onJoinChannelSuccess(channel, uid, elapsed);
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    setupLocalVideo();
                }
            });
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wawaji_server);

        if (checkSelfPermission(Manifest.permission.RECORD_AUDIO, PERMISSION_REQ_ID_RECORD_AUDIO)
                && checkSelfPermission(Manifest.permission.CAMERA, PERMISSION_REQ_ID_CAMERA)) {
            initAgoraEngineAndJoinChannel();
        }
    }

    private void initAgoraEngineAndJoinChannel() {
        setupUI();                   // Step 1
        initializeAgoraEngine();     // Step 2
        setupVideoProfile();         // Step 3
        joinChannel();               // Step 4
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
            case PERMISSION_REQ_ID_RECORD_AUDIO: {
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    checkSelfPermission(Manifest.permission.CAMERA, PERMISSION_REQ_ID_CAMERA);
                } else {
                    showLongToast("No permission for " + Manifest.permission.RECORD_AUDIO);
                    finish();
                }
                break;
            }
            case PERMISSION_REQ_ID_CAMERA: {
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    initAgoraEngineAndJoinChannel();
                } else {
                    showLongToast("No permission for " + Manifest.permission.CAMERA);
                    finish();
                }
                break;
            }
        }
    }

    public final void showLongToast(final String msg) {
        this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_LONG).show();
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        leaveChannel();
        RtcEngine.destroy();
        mRtcEngine = null;
    }

    // Step 1
    private void setupUI() {
        Intent intent = getIntent();
        channelName = intent.getStringExtra(Constant.CHANNEL_NAME);
        if (channelName != null) {
            TextView mTextChannel = (TextView) findViewById(R.id.room_name);
            mTextChannel.setText(channelName);
        }

        appid = intent.getStringExtra(Constant.CHANNEL_APPID);
        uid = intent.getIntExtra(Constant.CHANNEL_UID, 0);
        useCaptureFormatNV21 = intent.getBooleanExtra(Constant.CHANNEL_SET_NV21, false);
        openRtmpStream = intent.getBooleanExtra(Constant.CHANNEL_URL_STATE, false);

        if (openRtmpStream) {
            rtmpUrl = intent.getStringExtra(Constant.CHANNEL_URL);
            width = intent.getIntExtra(Constant.CHANNEL_URL_W, 0);
            height = intent.getIntExtra(Constant.CHANNEL_URL_H, 0);
            bitrate = intent.getIntExtra(Constant.CHANNEL_URL_BITRATE, 0);
            fps = intent.getIntExtra(Constant.CHANNEL_URL_FPS, 0);
        }

    }

    // Step 2
    private void initializeAgoraEngine() {
        try {
            if (appid.equals("")) {
                appid = getString(R.string.agora_app_id);
            }
            mRtcEngine = RtcEngine.create(getBaseContext(), appid, mRtcEventHandler);
        } catch (Exception e) {
            WawajiApplication.the().setSetting("appid", "");
            Log.e(LOG_TAG, Log.getStackTraceString(e));

            throw new RuntimeException("NEED TO check rtc sdk init fatal error\n" + Log.getStackTraceString(e));
        }
    }

    // Step 3
    private void setupVideoProfile() {
        mRtcEngine.setChannelProfile(Constants.CHANNEL_PROFILE_LIVE_BROADCASTING);
        mRtcEngine.enableVideo();
        mRtcEngine.setClientRole(Constants.CLIENT_ROLE_BROADCASTER);
        mRtcEngine.setVideoProfile(Constants.VIDEO_PROFILE_360P, false);
        mRtcEngine.muteAllRemoteAudioStreams(true);
        mRtcEngine.muteAllRemoteVideoStreams(true);
        mRtcEngine.enableWebSdkInteroperability(true);
        mRtcEngine.muteLocalAudioStream(true);
        if (useCaptureFormatNV21){
            mRtcEngine.setParameters("{\"che.video.captureFormatNV21\": true}");
        }

        if (openRtmpStream && !rtmpUrl.equals("") && width != 0 && height != 0 && bitrate != 0 && fps != 0) {
            PublisherConfiguration config = new PublisherConfiguration.Builder()
                    .owner(true)
                    .size(width, height)
                    .frameRate(fps)
                    .bitRate(bitrate)
                    .rawStreamUrl(rtmpUrl)
                    .extraInfo("{\"lowDelay\":true}")
                    .build();

            mRtcEngine.configPublisher(config);
        }
    }


    // Step 4
    private void joinChannel() {

        mRtcEngine.joinChannel(null, channelName, "Extra Optional Data", uid); // if you do not specify the uid, we will generate the uid for you

    }

    // Step 5
    private void setupLocalVideo() {
        FrameLayout container = (FrameLayout) findViewById(R.id.local_video_view_container);
        SurfaceView surfaceView = RtcEngine.CreateRendererView(getBaseContext());
        surfaceView.setZOrderMediaOverlay(true);
        container.addView(surfaceView);
        mRtcEngine.setupLocalVideo(new VideoCanvas(surfaceView, VideoCanvas.RENDER_MODE_ADAPTIVE, 0));

    }

    // Step 6
    public void onSwitchCameraClicked(View view) {
        mRtcEngine.switchCamera();
    }

    // Step 7
    public void onLeaveGameClicked(View view) {
        finish();
    }

    // Step 8
    private void leaveChannel() {
        mRtcEngine.leaveChannel();
    }
}

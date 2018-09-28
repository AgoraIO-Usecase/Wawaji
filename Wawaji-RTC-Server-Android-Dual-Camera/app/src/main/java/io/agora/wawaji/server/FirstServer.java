package io.agora.wawaji.server;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.SurfaceView;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

import io.agora.rtc.live.LiveTranscoding;
import io.agora.rtc.Constants;
import io.agora.rtc.IRtcEngineEventHandler;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;
import io.agora.rtc.video.VideoEncoderConfiguration;
import io.agora.wawaji.utils.Constant;


public class FirstServer extends Activity {

    private static final String LOG_TAG = "firstTest-->";

    private static final int PERMISSION_REQ_ID_RECORD_AUDIO = 22;
    private static final int PERMISSION_REQ_ID_CAMERA = PERMISSION_REQ_ID_RECORD_AUDIO + 1;

    private Intent servicePushIntent;

    private RtcEngine mRtcEngine;
    private LiveTranscoding mLiveTranscoding;

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

    private int encodeWidth;
    private int encodeHeight;

    private final IRtcEngineEventHandler mRtcEventHandler = new IRtcEngineEventHandler() {

        @Override
        public void onJoinChannelSuccess(String channel, final int uid, int elapsed) {
            super.onJoinChannelSuccess(channel, uid, elapsed);
            Log.e("wbsTest", "FirstServer onJoinChannelSuccess()");
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    setupLocalVideo();
                    if (openRtmpStream1) {
                        setTranscoding(uid);
                        mRtcEngine.addPublishStreamUrl(rtmpUrl1, true);
                    }

                }
            });
        }

        @Override
        public void onError(int err) {
            super.onError(err);
        }

        @Override
        public void onWarning(int warn) {
            super.onWarning(warn);
        }

        @Override
        public void onStreamUnpublished(String url) {
            super.onStreamUnpublished(url);
            Log.e(LOG_TAG, "yty onStreamUnpublished " + url);
        }

        @Override
        public void onStreamPublished(String url, int error) {
            super.onStreamPublished(url, error);
            Log.e(LOG_TAG, "yty onStreamPublished " + error);
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

    private void setupUI() {
        Intent intent = getIntent();
        channelName = intent.getStringExtra(Constant.CHANNEL_NAME);
        if (channelName != null) {
            TextView mTextChannel = (TextView) findViewById(R.id.room_name);
            mTextChannel.setText(channelName);
        }

        appid = intent.getStringExtra(Constant.CHANNEL_APPID);
        uid1 = intent.getIntExtra(Constant.CHANNEL_UID1, 1);
        openRtmpStream1 = intent.getBooleanExtra(Constant.CHANNEL_URL_STATE1, false);

        if (openRtmpStream1) {
            rtmpUrl1 = intent.getStringExtra(Constant.CHANNEL_URL1);
            width1 = intent.getIntExtra(Constant.CHANNEL_URL_W1, 0);
            height1 = intent.getIntExtra(Constant.CHANNEL_URL_H1, 0);
            bitrate1 = intent.getIntExtra(Constant.CHANNEL_URL_BITRATE1, 0);
            fps1 = intent.getIntExtra(Constant.CHANNEL_URL_FPS1, 0);

        }
        uid2 = intent.getIntExtra(Constant.CHANNEL_UID2, 2);
        openRtmpStream2 = intent.getBooleanExtra(Constant.CHANNEL_URL_STATE2, false);
        if (openRtmpStream2) {
            rtmpUrl2 = intent.getStringExtra(Constant.CHANNEL_URL2);
            width2 = intent.getIntExtra(Constant.CHANNEL_URL_W2, 0);
            height2 = intent.getIntExtra(Constant.CHANNEL_URL_H2, 0);
            bitrate2 = intent.getIntExtra(Constant.CHANNEL_URL_BITRATE2, 0);
            fps2 = intent.getIntExtra(Constant.CHANNEL_URL_FPS2, 0);
        }

    }

    private void initAgoraEngineAndJoinChannel() {
        setupUI();
        initializeAgoraEngine();     // Step 2
        setupVideoProfile();         // Step 3
        joinChannel();               // Step 4

        startSecondProcess();

    }

    public boolean checkSelfPermission(String permission, int requestCode) {
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

        if (mRtcEngine != null) {
            mRtcEngine.leaveChannel();
            if (openRtmpStream1) {
                mRtcEngine.removePublishStreamUrl(rtmpUrl1);
            }

        }

        if (servicePushIntent != null) {
            stopService(servicePushIntent);
        }

        mRtcEngine = null;

        RtcEngine.destroy();
    }

    // Step 1
    private void initializeAgoraEngine() {
        try {
            mRtcEngine = RtcEngine.create(getBaseContext(), getResources().getString(R.string.agora_app_id), mRtcEventHandler);
        } catch (Exception e) {
            Log.e(LOG_TAG, Log.getStackTraceString(e));

            throw new RuntimeException("NEED TO check rtc sdk init fatal error\n" + Log.getStackTraceString(e));
        }
    }

    // Step 2
    private void setupVideoProfile() {
        mRtcEngine.setChannelProfile(Constants.CHANNEL_PROFILE_LIVE_BROADCASTING);
        mRtcEngine.enableVideo();
        mRtcEngine.setClientRole(Constants.CLIENT_ROLE_BROADCASTER);

        int vProfile = Constant.VIDEO_PROFILES[WawajiApplication.the().getSetting(Constant.PREF_PROPERTY_PROFILE_IDX, Constant.DEFAULT_PROFILE_IDX)];
        if (vProfile == Constants.VIDEO_PROFILE_360P) {
            encodeWidth = 640;
            encodeHeight = 360;
        } else if (vProfile == Constants.VIDEO_PROFILE_480P) {
            encodeWidth = 640;
            encodeHeight = 480;
        } else if (vProfile == Constants.VIDEO_PROFILE_720P) {
            encodeWidth = 1280;
            encodeHeight = 720;
        }

        //mRtcEngine.setVideoProfile(vProfile, false);
        VideoEncoderConfiguration encodeConfig = new VideoEncoderConfiguration(new VideoEncoderConfiguration.VideoDimensions(encodeWidth, encodeHeight),
                VideoEncoderConfiguration.FRAME_RATE.FRAME_RATE_FPS_15, VideoEncoderConfiguration.STANDARD_BITRATE,
                VideoEncoderConfiguration.ORIENTATION_MODE.ORIENTATION_MODE_FIXED_LANDSCAPE);
        mRtcEngine.setVideoEncoderConfiguration(encodeConfig);

        mRtcEngine.muteAllRemoteAudioStreams(true);
        mRtcEngine.muteAllRemoteVideoStreams(true);
        mRtcEngine.enableWebSdkInteroperability(true);
        mRtcEngine.muteLocalAudioStream(true);
    }


    // Step 3
    private void joinChannel() {
        mRtcEngine.joinChannel(null, channelName, "Extra Optional Data", uid1); // if you do not specify the uid, we will generate the uid for you
        if (openRtmpStream1) {
            initTranscoding();
        }

    }

    // Step 4
    private void setupLocalVideo() { //(int) ((Constant.SCREEN_WIDTH >> 1 )/ scale)
        FrameLayout container = (FrameLayout) findViewById(R.id.local_video_view_container);
        float scale = (float) (1.0 * encodeWidth / encodeHeight);

        DisplayMetrics metric = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metric);
        int screenWidth = metric.widthPixels;
        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(screenWidth >> 1, (int) ((screenWidth >> 1) / scale));
        layoutParams.addRule(RelativeLayout.CENTER_VERTICAL);
        container.setLayoutParams(layoutParams);
        SurfaceView surfaceView = RtcEngine.CreateRendererView(getBaseContext());
        surfaceView.setZOrderMediaOverlay(true);
        container.addView(surfaceView);
        mRtcEngine.setupLocalVideo(new VideoCanvas(surfaceView, VideoCanvas.RENDER_MODE_ADAPTIVE, 0));


    }

    // Step 7
    public void onLeaveGameClicked(View view) {
        finish();
    }

    private void startSecondProcess() {

        if (servicePushIntent == null) {
            servicePushIntent = new Intent();
            servicePushIntent.setAction("io.agora.wawaji.server.secondserver");
            servicePushIntent.setPackage(getPackageName());

            servicePushIntent.putExtra(Constant.CHANNEL_NAME, channelName);
            servicePushIntent.putExtra(Constant.CHANNEL_URL_STATE2, openRtmpStream2);
            servicePushIntent.putExtra(Constant.CHANNEL_UID2, uid2);

            if (openRtmpStream2) {
                servicePushIntent.putExtra(Constant.CHANNEL_URL2, rtmpUrl2);
                servicePushIntent.putExtra(Constant.CHANNEL_URL_W2, width2);
                servicePushIntent.putExtra(Constant.CHANNEL_URL_H2, height2);
                servicePushIntent.putExtra(Constant.CHANNEL_URL_BITRATE2, bitrate2);
                servicePushIntent.putExtra(Constant.CHANNEL_URL_FPS2, fps2);
            }

        }

        startService(servicePushIntent);

    }

    private void initTranscoding() {
        if (mLiveTranscoding == null) {
            mLiveTranscoding = new LiveTranscoding();
            mLiveTranscoding.width = width1;
            mLiveTranscoding.height = height1;
            mLiveTranscoding.lowLatency = true;
            mLiveTranscoding.videoBitrate = bitrate1;
            // if you want high fps, modify videoFramerate
            mLiveTranscoding.videoFramerate = fps1;
        }

        mRtcEngine.setLiveTranscoding(mLiveTranscoding);
    }

    private void setTranscoding(int uid) {
        mLiveTranscoding.setUsers(cdnLayout(uid, width1, height1));
        mLiveTranscoding.userCount = 1;
        mRtcEngine.setLiveTranscoding(mLiveTranscoding);
    }

    public static ArrayList<LiveTranscoding.TranscodingUser> cdnLayout(int uid, int width, int height) {

        ArrayList<LiveTranscoding.TranscodingUser> users = new ArrayList<>(1);

        LiveTranscoding.TranscodingUser user0 = new LiveTranscoding.TranscodingUser();
        user0.uid = uid;
        user0.alpha = 1;
        user0.zOrder = 0;
        user0.audioChannel = 0;

        user0.x = 0;
        user0.y = 0;
        user0.width = width;
        user0.height = height;
        users.add(user0);

        return users;
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.i(LOG_TAG, "onPause "  + servicePushIntent);
        if(servicePushIntent != null) {
           Intent intent = new Intent() ;
            intent.setAction("action1");
            intent.putExtra("status", 1);
            sendBroadcast(intent);
        }
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.i(LOG_TAG, "onRestart "  + servicePushIntent);
        if(servicePushIntent != null) {
            Intent intent = new Intent() ;
            intent.setAction("action1");
            intent.putExtra("status", 2);
            sendBroadcast(intent);
        }
    }


}

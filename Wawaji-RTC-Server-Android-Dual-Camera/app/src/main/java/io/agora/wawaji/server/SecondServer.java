package io.agora.wawaji.server;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.PixelFormat;
import android.os.IBinder;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.SurfaceView;
import android.view.View;
import android.view.WindowManager;
import android.widget.Toast;

import java.util.ArrayList;

import io.agora.rtc.Constants;
import io.agora.rtc.IRtcEngineEventHandler;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.live.LiveTranscoding;
import io.agora.rtc.video.AgoraVideoFrame;
import io.agora.rtc.video.VideoEncoderConfiguration;
import io.agora.wawaji.utils.CameraHelper;
import io.agora.wawaji.utils.Constant;

public class SecondServer extends Service implements IFrameListener {
    private static final String LOG_TAG = "wawaji_second_svr";

    private WindowManager mWindowManager;
    private WindowManager.LayoutParams mLayoutParams;
    private LayoutInflater mLayoutInflater;
    private View mFloatView;
    private int mCurrentX;
    private int mCurrentY;

    private RtcEngine mRtcEngine;
    private SurfaceView v;

    private String channelName = "";
    private String rtmpUrl2 = "";
    private int uid2 = 0;
    private int width2 = 0;
    private int height2 = 0;
    private int bitrate2 = 0;
    private int fps2 = 0;
    private boolean openRtmpStream2 = false;
    private Intent intent;
    private int encodeWidth;
    private int encodeHeight;

    private LiveTranscoding mLiveTranscoding;

    @Override
    public void onCreate() {
        super.onCreate();
        mWindowManager = (WindowManager) getApplicationContext().getSystemService(Context.WINDOW_SERVICE);
        mLayoutInflater = LayoutInflater.from(this);

        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("action1");
        registerReceiver(broadcastReceiver, intentFilter);
    }

    private void getParameterData() {
        if (this.intent != null) {
            channelName = intent.getStringExtra(Constant.CHANNEL_NAME);
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
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.i(LOG_TAG, "onStartCommand" + intent);
        this.intent = intent;
        getParameterData();

        if (mRtcEngine == null) {
            joinChannel();
            createView();
        }
        return super.onStartCommand(intent, flags, startId);
    }

    private void createView() {

        if (mFloatView == null) {
            mFloatView = mLayoutInflater.inflate(R.layout.service_main, null);
            // mFloatView.setOnTouchListener(new OnFloatViewTouchListener());
            mLayoutParams = new WindowManager.LayoutParams();
            mLayoutParams.gravity = Gravity.LEFT | Gravity.CENTER;
            mLayoutParams.type = WindowManager.LayoutParams.TYPE_PHONE;
            mLayoutParams.format = PixelFormat.RGBA_8888;
            mLayoutParams.flags = WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;

            DisplayMetrics metric = new DisplayMetrics();
            mWindowManager.getDefaultDisplay().getMetrics(metric);
            int screenWidth = metric.widthPixels;

            mCurrentX = mLayoutParams.x = screenWidth >> 1;
            mCurrentY = mLayoutParams.y = 0;

            float scale = (float) (1.0 * encodeWidth / encodeHeight);
            // set default view size

            mLayoutParams.width = screenWidth >> 1;
            mLayoutParams.height = (int) ((screenWidth >> 1) / scale);

            mFloatView.setBackgroundResource(R.color.agora_blue);
            mWindowManager.addView(mFloatView, mLayoutParams);
        }

        if (v == null) {
            v = (SurfaceView) mFloatView.findViewById(R.id.sv_service_view);
            v.setZOrderOnTop(true);
            new CameraHelper(v, encodeWidth, encodeHeight, this);
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    private void updateFloatView() {
        mLayoutParams.x = mCurrentX;
        mLayoutParams.y = mCurrentY;
        mWindowManager.updateViewLayout(mFloatView, mLayoutParams);
    }

    private class OnFloatViewTouchListener implements View.OnTouchListener {
        @Override
        public boolean onTouch(View v, MotionEvent event) {
            mCurrentX = (int) event.getRawX() - 50;
            mCurrentY = (int) event.getRawY() - 50;
            int action = event.getAction();
            switch (action) {
                case MotionEvent.ACTION_DOWN:
                    break;
                case MotionEvent.ACTION_MOVE:
                    updateFloatView();
                    break;
                case MotionEvent.ACTION_UP:
                    break;
            }
            return true;
        }
    }

    private IRtcEngineEventHandler mRtcEventHandler = new IRtcEngineEventHandler() {
        @Override
        public void onJoinChannelSuccess(String channel, final int uid, int elapsed) {
            super.onJoinChannelSuccess(channel, uid, elapsed);
            Log.e(LOG_TAG, "SecondServer onJoinChannelSuccess()");

            if (openRtmpStream2) {

                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        setTranscoding(uid);
                        mRtcEngine.addPublishStreamUrl(rtmpUrl2, true);
                    }
                }).start();
            }

        }

        @Override
        public void onError(int err) {
            super.onError(err);
            Toast.makeText(SecondServer.this, "SecondServer RtcEngine.onError: " + err, Toast.LENGTH_LONG).show();
        }

        @Override
        public void onWarning(int warn) {
            super.onWarning(warn);
            Toast.makeText(SecondServer.this, "SecondServer RtcEngine.onWarning: " + warn, Toast.LENGTH_LONG).show();
        }

        @Override
        public void onStreamPublished(String url, int error) {
            super.onStreamPublished(url, error);

            Log.e(LOG_TAG, "onStreamPublished()" + error);
        }

        @Override
        public void onStreamUnpublished(String url) {
            super.onStreamUnpublished(url);
        }
    };

    public void joinChannel() {
        try {
            mRtcEngine = RtcEngine.create(getApplicationContext(), getResources().getString(R.string.agora_app_id), mRtcEventHandler);
        } catch (Exception e) {
            throw new RuntimeException("NEED TO check rtc sdk init fatal error\n" + Log.getStackTraceString(e));
        }

        setupVideoProfile();

        if (openRtmpStream2) {
            initTranscoding();
        }
        mRtcEngine.joinChannel(null, channelName, "", uid2); // if you do not specify the uid, we will generate the uid for you

    }

    private void setupVideoProfile() {
        mRtcEngine.setChannelProfile(Constants.CHANNEL_PROFILE_LIVE_BROADCASTING);
        mRtcEngine.setExternalVideoSource(true, false, false);
        mRtcEngine.enableVideo();
        mRtcEngine.setClientRole(Constants.CLIENT_ROLE_BROADCASTER);
        // choose the same video profile
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

    @Override
    public void onFrameValid(final AgoraVideoFrame frame) {
        // to be sure the RtcEngine has been inited
        if (mRtcEngine != null)
            mRtcEngine.pushExternalVideoFrame(frame);
    }

    private void initTranscoding() {
        if (mLiveTranscoding == null) {
            mLiveTranscoding = new LiveTranscoding();
            mLiveTranscoding.width = width2;
            mLiveTranscoding.height = height2;
            mLiveTranscoding.lowLatency = true;
            mLiveTranscoding.videoBitrate = bitrate2;
            // if you want high fps, modify videoFramerate
            mLiveTranscoding.videoFramerate = fps2;
        }

        mRtcEngine.setLiveTranscoding(mLiveTranscoding);
    }

    private void setTranscoding(int uid) {
        mLiveTranscoding.setUsers(cdnLayout(uid, width2, height2));
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
    public void onDestroy() {
        super.onDestroy();
        Log.e(LOG_TAG, "on Server Destroy");
        if (mRtcEngine != null) {
            if (openRtmpStream2) {
                mRtcEngine.removePublishStreamUrl(rtmpUrl2);
            }
            mRtcEngine.leaveChannel();
            mWindowManager.removeView(mFloatView);
        }
        unregisterReceiver(broadcastReceiver);

        System.exit(0);
    }

    public void onPause() {
        Log.i(LOG_TAG, "onPause " + mWindowManager);
        if (mWindowManager != null) {
            mFloatView.setVisibility(View.GONE);

        }

    }

    public void onResume() {
        Log.i(LOG_TAG, "onResume " + mWindowManager);
        if (mWindowManager != null) {
            mFloatView.setVisibility(View.VISIBLE);
        }

    }

    private BroadcastReceiver broadcastReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            Log.i(LOG_TAG, "action " + action);
            if (action.equals("action1")) {
                if (intent.getIntExtra("status", 0) == 1) {
                    onPause();

                } else if (intent.getIntExtra("status", 0) == 2) {
                    onResume();

                }
            }
        }
    };
}
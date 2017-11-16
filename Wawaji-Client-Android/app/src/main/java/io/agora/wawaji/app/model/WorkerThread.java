package io.agora.wawaji.app.model;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.*;
import android.preference.PreferenceManager;
import android.provider.Settings;
import android.text.TextUtils;
import android.util.Log;
import android.view.SurfaceView;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import io.agora.AgoraAPIOnlySignal;
import io.agora.common.Constant;
import io.agora.common.TokenUtils;
import io.agora.rtc.Constants;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;
import io.agora.wawaji.app.BuildConfig;
import io.agora.wawaji.app.R;
import org.java_websocket.client.WebSocketClient;
import org.java_websocket.handshake.ServerHandshake;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.File;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.Locale;
import java.util.concurrent.CountDownLatch;

import static io.agora.common.Constant.*;

public class WorkerThread extends Thread {
    private final static Logger log = LoggerFactory.getLogger(WorkerThread.class);

    private final Context mContext;

    private static final int ACTION_WORKER_THREAD_QUIT = 0X1010; // quit this thread

    private static final int ACTION_WORKER_JOIN_CHANNEL = 0X2010;

    private static final int ACTION_WORKER_LEAVE_CHANNEL = 0X2011;

    private static final int ACTION_WORKER_CONFIG_ENGINE = 0X2012;

    private static final int ACTION_WORKER_PREVIEW = 0X2014;

    private static final int ACTION_WORKER_WAWAJI_PREPARE = 0X2015;

    private static final int ACTION_WORKER_WAWAJI_CTRL = 0X2016;

    private static final class WorkerThreadHandler extends Handler {

        private WorkerThread mWorkerThread;

        WorkerThreadHandler(WorkerThread thread) {
            this.mWorkerThread = thread;
        }

        public void release() {
            mWorkerThread = null;
        }

        @Override
        public void handleMessage(Message msg) {
            if (this.mWorkerThread == null) {
                log.warn("handler is already released! " + msg.what);
                return;
            }

            switch (msg.what) {
                case ACTION_WORKER_THREAD_QUIT:
                    mWorkerThread.exit();
                    break;
                case ACTION_WORKER_JOIN_CHANNEL:
                    String[] data = (String[]) msg.obj;
                    mWorkerThread.joinChannel(data[0], msg.arg1);
                    break;
                case ACTION_WORKER_LEAVE_CHANNEL:
                    String channel = (String) msg.obj;
                    mWorkerThread.leaveChannel(channel);
                    break;
                case ACTION_WORKER_CONFIG_ENGINE:
                    Object[] configData = (Object[]) msg.obj;
                    mWorkerThread.configEngine((int) configData[0], (int) configData[1]);
                    break;
                case ACTION_WORKER_PREVIEW:
                    Object[] previewData = (Object[]) msg.obj;
                    mWorkerThread.preview((boolean) previewData[0], (SurfaceView) previewData[1], (int) previewData[2]);
                    break;
                case ACTION_WORKER_WAWAJI_PREPARE:
                    mWorkerThread.prepareWawaji();
                    break;
                case ACTION_WORKER_WAWAJI_CTRL:
                    mWorkerThread.ctrlWawaji(msg.arg1);
                    break;
            }
        }
    }

    private WorkerThreadHandler mWorkerHandler;

    private boolean mReady;

    public final void waitForReady() {
        while (!mReady) {
            try {
                Thread.sleep(20);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            log.debug("wait for " + WorkerThread.class.getSimpleName());
        }
    }

    @Override
    public void run() {
        log.trace("start to run");
        Looper.prepare();

        mWorkerHandler = new WorkerThreadHandler(this);

        ensureRtcEngineReadyLock();

        mReady = true;

        // enter thread looper
        Looper.loop();
    }

    private RtcEngine mRtcEngine;

    private WebSocketClient mWawajiCtrl;

    public final void joinChannel(final String channel, int uid) {
        if (Thread.currentThread() != this) {
            log.warn("joinChannel() - worker thread asynchronously " + channel + " " + (uid & 0xFFFFFFFFL));
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_JOIN_CHANNEL;
            envelop.obj = new String[]{channel};
            envelop.arg1 = uid;
            mWorkerHandler.sendMessage(envelop);
            return;
        }

        ensureRtcEngineReadyLock();
        mRtcEngine.joinChannel(null, channel, "OpenLive", uid);

        ensureSignalingSDKReadyLock(false);
        mSignalSDK.channelLeave(channel);

        mEngineConfig.mChannel = channel;

        log.debug("joinChannel " + channel + " " + uid);
    }

    public final void leaveChannel(String channel) {
        if (Thread.currentThread() != this) {
            log.warn("leaveChannel() - worker thread asynchronously " + channel);
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_LEAVE_CHANNEL;
            envelop.obj = channel;
            mWorkerHandler.sendMessage(envelop);
            return;
        }

        if (mRtcEngine != null) {
            mRtcEngine.leaveChannel();
        }

        if (mSignalSDK != null) {
            mSignalSDK.channelLeave(mEngineConfig.mChannel);
        }

        if (mWawajiCtrl != null) {
            mWawajiCtrl.close();
            mWawajiCtrl = null;
        }

        int clientRole = mEngineConfig.mClientRole;
        mEngineConfig.reset();
        log.debug("leaveChannel " + channel + " " + clientRole);
    }

    private EngineConfig mEngineConfig;

    public final EngineConfig getEngineConfig() {
        return mEngineConfig;
    }

    private final MyEngineEventHandler mEngineEventHandler;

    public final void configEngine(int cRole, int vProfile) {
        if (Thread.currentThread() != this) {
            log.warn("configEngine() - worker thread asynchronously " + cRole + " " + vProfile);
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_CONFIG_ENGINE;
            envelop.obj = new Object[]{cRole, vProfile};
            mWorkerHandler.sendMessage(envelop);
            return;
        }

        ensureRtcEngineReadyLock();
        mEngineConfig.mClientRole = cRole;
        mEngineConfig.mVideoProfile = vProfile;

        mRtcEngine.setVideoProfile(mEngineConfig.mVideoProfile, true);

        mRtcEngine.setClientRole(cRole, "");

        if (cRole == Constants.CLIENT_ROLE_BROADCASTER) {
            mRtcEngine.setExternalVideoSource(true, false, true);
//        mRtcEngine.useExternalAudioDevice();
            mRtcEngine.muteLocalVideoStream(true);
            mRtcEngine.muteLocalAudioStream(true);

        }

        log.debug("configEngine " + cRole + " " + mEngineConfig.mVideoProfile);
    }

    private CountDownLatch mConnectLatch;
    private CountDownLatch mReadyLatch;

    public final void prepareWawaji() {
        if (Thread.currentThread() != this) {
            log.warn("prepareWawaji() - worker thread asynchronously");
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_WAWAJI_PREPARE;
            mWorkerHandler.sendMessage(envelop);
            return;
        }

        URI uri;
        try {
            uri = new URI(Constant.WAWAJI_SERVER_URL);
        } catch (URISyntaxException e) {
            log.error(Log.getStackTraceString(e));
            return;
        }

        mConnectLatch = new CountDownLatch(1);
        mReadyLatch = new CountDownLatch(1);

        mWawajiCtrl = new WebSocketClient(uri) {
            @Override
            public void onOpen(ServerHandshake serverHandshake) {
                log.debug("onOpen " + serverHandshake);
                mWawajiCtrl.send("Hello from " + Build.MANUFACTURER + " " + Build.MODEL);
                mConnectLatch.countDown();
            }

            @Override
            public void onMessage(String message) {
                log.debug("onMessage " + message);

                JsonParser parser = new JsonParser();
                JsonElement jElem = parser.parse(message);
                JsonObject obj = jElem.getAsJsonObject();
                jElem = obj.get("type");

                String type = jElem.getAsString();
                if ("Ready".equals(type)) {
                    mReadyLatch.countDown();
                } else if ("Time".equals(type)) {
                    jElem = obj.get("data");
                    int timeout = jElem.getAsInt();
                    WorkerThread.this.mEngineEventHandler.notifyAppLayer(Constant.Wawaji_Msg_TIMEOUT, timeout);
                } else if ("Result".equals(type)) {
                    jElem = obj.get("data");
                    boolean gotone = jElem.getAsBoolean();
                    WorkerThread.this.mEngineEventHandler.notifyAppLayer(Constant.Wawaji_Msg_RESULT, gotone);
                }
            }

            @Override
            public void onClose(int i, String s, boolean b) {
                log.debug("onClose " + i + " " + s + " " + b);
                WorkerThread.this.mEngineEventHandler.notifyAppLayer(Constant.Wawaji_Msg_FORCED_LOGOUT, s);
            }

            @Override
            public void onError(Exception e) {
                log.error("onError " + Log.getStackTraceString(e));
            }
        };

        mWawajiCtrl.connect();

        try {
            mConnectLatch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        log.debug("prepareWawaji " + " " + mEngineConfig.mVideoProfile + " " + mWawajiCtrl + " " + mConnectLatch.getCount());
    }

    public final void ctrlWawaji(int ctrl) {
        if (Thread.currentThread() != this) {
            log.warn("ctrlWawaji() - worker thread asynchronously " + ctrl);
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_WAWAJI_CTRL;
            envelop.arg1 = ctrl;
            mWorkerHandler.sendMessage(envelop);
            return;
        }

        if (mReadyLatch.getCount() > 0) {
            try {
                mReadyLatch.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        switch (ctrl) {
            case Wawaji_Ctrl_START:
                mWawajiCtrl.send("{\"type\":\"Insert\",\"data\":\"\",\"extra\":123456}");
                break;
            case Wawaji_Ctrl_DOWN:
                mWawajiCtrl.send("{\"type\":\"Control\",\"data\":\"d\"}");
                break;
            case Wawaji_Ctrl_UP:
                mWawajiCtrl.send("{\"type\":\"Control\",\"data\":\"u\"}");
                break;
            case Wawaji_Ctrl_LEFT:
                mWawajiCtrl.send("{\"type\":\"Control\",\"data\":\"l\"}");
                break;
            case Wawaji_Ctrl_RIGHT:
                mWawajiCtrl.send("{\"type\":\"Control\",\"data\":\"r\"}");
                break;
            case Wawaji_Ctrl_CATCH:
                mWawajiCtrl.send("{\"type\":\"Control\",\"data\":\"b\"}");
                break;
            case Wawaji_Ctrl_SWITCH_CAM:
                String switchCam = "{\"uid\":\"%s\",\"opeType\":1,\"opeAttr\":\"\"}";
                switchCam = String.format(Locale.US, switchCam, String.valueOf(mEngineConfig.mUid));
                mSignalSDK.messageInstantSend("meixi", mEngineConfig.mWawajiUid, switchCam, String.valueOf(System.currentTimeMillis()));
                break;
            default:
                log.warn("Unknown ctrl " + ctrl);
                break;
        }

        log.warn("ctrlWawaji done " + ctrl + " " + mReadyLatch.getCount());
    }

    public final void preview(boolean start, SurfaceView view, int uid) {
        if (Thread.currentThread() != this) {
            log.warn("preview() - worker thread asynchronously " + start + " " + view + " " + (uid & 0XFFFFFFFFL));
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_PREVIEW;
            envelop.obj = new Object[]{start, view, uid};
            mWorkerHandler.sendMessage(envelop);
            return;
        }

        ensureRtcEngineReadyLock();
        if (start) {
            mRtcEngine.setupLocalVideo(new VideoCanvas(view, VideoCanvas.RENDER_MODE_HIDDEN, uid));
            mRtcEngine.startPreview();
        } else {
            mRtcEngine.stopPreview();
        }
    }

    public static String getDeviceID(Context context) {
        // XXX according to the API docs, this value may change after factory reset
        // use Android id as device id
        return Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID);
    }

    private RtcEngine ensureRtcEngineReadyLock() {
        if (mRtcEngine == null) {
            String appId = mContext.getString(R.string.private_app_id);
            if (TextUtils.isEmpty(appId)) {
                throw new RuntimeException("NEED TO use your App ID, get your own ID at https://dashboard.agora.io/");
            }
            try {
                mRtcEngine = RtcEngine.create(mContext, appId, mEngineEventHandler.mRtcEventHandler);
            } catch (Exception e) {
                log.error(Log.getStackTraceString(e));
                throw new RuntimeException("NEED TO check rtc sdk init fatal error\n" + Log.getStackTraceString(e));
            }
            mRtcEngine.setChannelProfile(Constants.CHANNEL_PROFILE_LIVE_BROADCASTING);
            mRtcEngine.enableVideo();
            mRtcEngine.setLogFile(Environment.getExternalStorageDirectory()
                    + File.separator + mContext.getPackageName() + "/log/agora-rtc.log");
            mRtcEngine.enableDualStreamMode(true);
        }
        return mRtcEngine;
    }

    private AgoraAPIOnlySignal mSignalSDK;

    private AgoraAPIOnlySignal ensureSignalingSDKReadyLock(boolean logout) {
        String appId = mContext.getString(R.string.agora_app_id);
        if (mSignalSDK == null) {
            mSignalSDK = AgoraAPIOnlySignal.getInstance(mContext, appId);
        }

        if (logout) {
            mSignalSDK.logout();
        }

        mSignalSDK.callbackSet(mEngineEventHandler.mSignalingEventHandler);
        String identification = "p1_" + getDeviceID(mContext) + "_a" + BuildConfig.APPLICATION_ID + "_v" + BuildConfig.VERSION_NAME;

        long expiredTime = System.currentTimeMillis() / 1000 + 3600;
        String token = TokenUtils.calcToken(appId, mContext.getString(R.string.agora_app_certificate), String.valueOf(mEngineConfig.mUid), expiredTime);

        mSignalSDK.login2(appId, String.valueOf(mEngineConfig.mUid), token, 0, "", 5, 1);
        log.debug("login " + (mEngineConfig.mUid & 0XFFFFFFFFL) + " " + identification);
        return mSignalSDK;
    }

    public MyEngineEventHandler eventHandler() {
        return mEngineEventHandler;
    }

    public RtcEngine getRtcEngine() {
        return mRtcEngine;
    }

    /**
     * call this method to exit
     * should ONLY call this method when this thread is running
     */
    public final void exit() {
        if (Thread.currentThread() != this) {
            log.warn("exit() - exit app thread asynchronously");
            mWorkerHandler.sendEmptyMessage(ACTION_WORKER_THREAD_QUIT);
            return;
        }

        mReady = false;

        // TODO should remove all pending(read) messages

        log.debug("exit() > start");

        // exit thread looper
        Looper.myLooper().quit();

        mWorkerHandler.release();

        log.debug("exit() > end");
    }

    public WorkerThread(Context context) {
        this.mContext = context;

        this.mEngineConfig = new EngineConfig();
        SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(context);
        this.mEngineConfig.mUid = pref.getInt(ConstantApp.PrefManager.PREF_PROPERTY_UID, 0);
        if (mEngineConfig.mUid == 0) {
            mEngineConfig.mUid = System.identityHashCode(System.currentTimeMillis());
            pref.edit().putInt(ConstantApp.PrefManager.PREF_PROPERTY_UID, mEngineConfig.mUid).apply();
        }

        this.mEngineEventHandler = new MyEngineEventHandler(mContext, this.mEngineConfig);
    }
}

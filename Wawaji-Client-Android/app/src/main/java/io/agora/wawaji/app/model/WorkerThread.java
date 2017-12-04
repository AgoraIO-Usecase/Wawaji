package io.agora.wawaji.app.model;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.preference.PreferenceManager;
import android.provider.Settings;
import android.text.TextUtils;
import android.util.Log;

import io.agora.AgoraAPIOnlySignal;
import io.agora.common.TokenUtils;
import io.agora.rtc.Constants;
import io.agora.rtc.RtcEngine;
import io.agora.wawaji.app.BuildConfig;
import io.agora.wawaji.app.R;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.File;

import static io.agora.common.Constant.*;

public class WorkerThread extends Thread {
    private final static Logger log = LoggerFactory.getLogger(WorkerThread.class);

    private final Context mContext;

    private static final int ACTION_WORKER_THREAD_QUIT = 0X1010; // quit this thread

    private static final int ACTION_WORKER_JOIN_CHANNEL = 0X2010;

    private static final int ACTION_WORKER_LEAVE_CHANNEL = 0X2011;

    private static final int ACTION_WORKER_CONFIG_ENGINE = 0X2012;

    private static final int ACTION_WORKER_PREVIEW = 0X2014;

    private static final int ACTION_WORKER_WAWAJI_FETCH = 0X2015;

    private static final int ACTION_WORKER_WAWAJI_PREPARE = 0X2016;

    private static final int ACTION_WORKER_WAWAJI_CTRL = 0X2017;

    private static final int ACTION_WORKER_WAWAJI_START = 0X2018;

    private static final int ACTION_WORKER_WAWAJI_JOINCHANNEL = 0X2019;

    private static final int ACTION_WORKER_WAWAJI_LEAVECHANNEL = 0X2020;

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
                    Bundle bundle = msg.getData();
                    mWorkerThread.joinChannel(bundle.getString("appid"), bundle.getString("appcertifer"), data[0], msg.arg1);
                    break;
                case ACTION_WORKER_LEAVE_CHANNEL:
                    String channel = (String) msg.obj;
                    mWorkerThread.leaveChannel(channel);
                    break;
                case ACTION_WORKER_CONFIG_ENGINE:
                    Object[] configData = (Object[]) msg.obj;
                    mWorkerThread.configEngine((int) configData[0], (int) configData[1], (String) configData[2]);
                    break;
                case ACTION_WORKER_WAWAJI_FETCH:
                    mWorkerThread.fetchWawaji();
                    break;
                case ACTION_WORKER_WAWAJI_CTRL:
                    mWorkerThread.ctrlWawaji((String) msg.obj, msg.arg1);
                    break;
                case ACTION_WORKER_WAWAJI_JOINCHANNEL:
                    mWorkerThread.joinSiginalChannel((String) msg.obj);
                    break;
                case ACTION_WORKER_WAWAJI_LEAVECHANNEL:
                    mWorkerThread.leaveChannel((String) msg.obj);
                    break;
                case ACTION_WORKER_WAWAJI_START:
                    mWorkerThread.startWawaji((String) msg.obj);
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
        mReady = true;
        // enter thread looper
        Looper.loop();
    }

    private RtcEngine mRtcEngine;

    public final void joinChannel(String appid, String appcertifer, final String channel, int uid) {
        if (Thread.currentThread() != this) {
            log.warn("joinChannel() - worker thread asynchronously " + channel + " " + (uid & 0xFFFFFFFFL));
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_JOIN_CHANNEL;
            envelop.obj = new String[]{channel};
            envelop.arg1 = uid;
            Bundle data = new Bundle();
            data.putString("appid", appid);
            data.putString("appcertifer", appcertifer);
            envelop.setData(data);
            mWorkerHandler.sendMessage(envelop);
            return;
        }
        ensureRtcEngineReadyLock(appid);
        if (appcertifer == null) {
            mRtcEngine.joinChannel(null, channel, "Wawa", uid);
        } else {
            String channelKey = TokenUtils.getDynamicKeyForJoinChannel(channel, uid, appid, appcertifer);
            mRtcEngine.joinChannel(channelKey, channel, "Wawa", uid);
        }
        ensureSignalingSDKReadyLock(false);

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

        int clientRole = mEngineConfig.mClientRole;
        mEngineConfig.reset();
        log.debug("leaveChannel " + channel + " " + clientRole);
    }

    private EngineConfig mEngineConfig;

    public final EngineConfig getEngineConfig() {
        return mEngineConfig;
    }

    private final MyEngineEventHandler mEngineEventHandler;

    public final void configEngine(int cRole, int vProfile, String appid) {
        if (Thread.currentThread() != this) {
            log.warn("configEngine() - worker thread asynchronously " + cRole + " " + vProfile);
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_CONFIG_ENGINE;
            envelop.obj = new Object[]{cRole, vProfile, appid};
            mWorkerHandler.sendMessage(envelop);
            return;
        }
        ensureRtcEngineReadyLock(appid);
        mEngineConfig.mClientRole = cRole;
        mEngineConfig.mVideoProfile = vProfile;

        mRtcEngine.setVideoProfile(mEngineConfig.mVideoProfile, true);

        mRtcEngine.setClientRole(cRole, "");

        if (cRole == Constants.CLIENT_ROLE_BROADCASTER) {
            mRtcEngine.setExternalVideoSource(true, false, true);
            mRtcEngine.muteLocalVideoStream(true);
            mRtcEngine.muteLocalAudioStream(true);
        }
        log.debug("configEngine " + cRole + " " + mEngineConfig.mVideoProfile);
    }

    public final void fetchWawaji() {
        if (Thread.currentThread() != this) {
            log.warn("fetchWawaji() - worker thread asynchronously");
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_WAWAJI_FETCH;
            mWorkerHandler.sendMessage(envelop);
            return;
        }
        ensureSignalingSDKReadyLock(false);

        mSignalSDK.messageInstantSend(WAWAJI_CONTROL_CENTER, 0, "{ \"type\": \"LIST\" }", String.valueOf(System.currentTimeMillis()));
    }

    public final void startWawaji(String machineName) {
        if (Thread.currentThread() != this) {
            log.warn("startWawaji() - worker thread asynchronously");
            Message envelop = new Message();
            envelop.obj = machineName;
            envelop.what = ACTION_WORKER_WAWAJI_START;
            mWorkerHandler.sendMessage(envelop);
            return;
        }

        mSignalSDK.messageInstantSend(machineName, 0, "{\"type\":\"START\"}", String.valueOf(System.currentTimeMillis()));
    }

    public final void joinSiginalChannel(String channelName) {
        log.debug("joinSiginalChannel channelName :" + channelName);
        if (Thread.currentThread() != this) {
            log.warn("joinSiginalChannel() - worker thread asynchronously");
            Message envelop = new Message();
            envelop.obj = channelName;
            envelop.what = ACTION_WORKER_WAWAJI_JOINCHANNEL;
            mWorkerHandler.sendMessage(envelop);
            return;
        }
        log.debug("joinSiginalChannel mSignalSDK :" + mSignalSDK);
        mSignalSDK.channelJoin(channelName);
    }


    public final void leaveSiginalChannel(String channelName) {
        log.debug("leaveSiginalChannel channelName :" + channelName);
        if (Thread.currentThread() != this) {
            log.warn("leaveSiginalChannel() - worker thread asynchronously");
            Message envelop = new Message();
            envelop.obj = channelName;
            envelop.what = ACTION_WORKER_WAWAJI_LEAVECHANNEL;
            mWorkerHandler.sendMessage(envelop);
            return;
        }
        log.debug("leaveSiginalChannel mSignalSDK :" + mSignalSDK);
        mSignalSDK.channelLeave(channelName);
    }

    public final void ctrlWawaji(String signalRoomName, int ctrl) {
        if (Thread.currentThread() != this) {
            log.warn("ctrlWawaji() - worker thread asynchronously " + ctrl);
            Message envelop = new Message();
            envelop.what = ACTION_WORKER_WAWAJI_CTRL;
            envelop.arg1 = ctrl;
            envelop.obj = signalRoomName;
            mWorkerHandler.sendMessage(envelop);
            return;
        }

        switch (ctrl) {
            case Wawaji_Ctrl_PLAY:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"PLAY\"}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_DOWN:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"CONTROL\",\"data\":\"down\",\"pressed\":true}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_DOWN_STOP:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"CONTROL\",\"data\":\"down\",\"pressed\":false}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_UP:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"CONTROL\",\"data\":\"up\",\"pressed\":true}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_UP_STOP:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"CONTROL\",\"data\":\"up\",\"pressed\":false}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_LEFT:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"CONTROL\",\"data\":\"left\",\"pressed\":true}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_LEFT_STOP:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"CONTROL\",\"data\":\"left\",\"pressed\":false}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_RIGHT:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"CONTROL\",\"data\":\"right\",\"pressed\":true}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_RIGHT_STOP:
                mSignalSDK.messageChannelSend(signalRoomName, "{\"type\":\"CONTROL\",\"data\":\"right\",\"pressed\":false}", String.valueOf(System.currentTimeMillis()));
                break;
            case Wawaji_Ctrl_CATCH:
                mSignalSDK.messageChannelSend(signalRoomName, "{ \"type\":\"CATCH\"}", String.valueOf(System.currentTimeMillis()));
                break;
            default:
                log.warn("Unknown ctrl " + ctrl);
                break;
        }
        log.warn("ctrlWawaji done " + ctrl + " " + signalRoomName);
    }


    public static String getDeviceID(Context context) {
        // XXX according to the API docs, this value may change after factory reset
        // use Android id as device id
        return Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID);
    }

    private RtcEngine ensureRtcEngineReadyLock(String appId) {
        if (mRtcEngine == null) {
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
        String appId = mContext.getString(R.string.agora_app_id_signal);
        if (mSignalSDK == null) {
            mSignalSDK = AgoraAPIOnlySignal.getInstance(mContext, appId);
        }

        if (logout) {
            mSignalSDK.logout();
        }

        mSignalSDK.callbackSet(mEngineEventHandler.mSignalingEventHandler);
        String identification = "p1_" + getDeviceID(mContext) + "_a" + BuildConfig.APPLICATION_ID + "_v" + BuildConfig.VERSION_NAME;
        log.debug("ensureSignalingSDKReadyLock mEngineConfig.mUid :" + mEngineConfig.mUid);

        long expiredTime = System.currentTimeMillis() / 1000 + 3600;
        String token = TokenUtils.calcToken(appId, mContext.getString(R.string.agora_app_certificate_signal), String.valueOf(mEngineConfig.mUid), expiredTime);

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

    public void destroyRtcEngine() {
        if (mRtcEngine != null) {
            mRtcEngine = null;
        }
    }
}

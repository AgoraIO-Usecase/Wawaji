package io.agora.wawaji.app.model;

import android.content.Context;
import io.agora.AgoraAPIOnlySignal;
import io.agora.rtc.IRtcEngineEventHandler;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.Arrays;
import java.util.Iterator;
import java.util.concurrent.ConcurrentHashMap;

public class MyEngineEventHandler {
    public MyEngineEventHandler(Context ctx, EngineConfig config) {
        this.mContext = ctx;
        this.mConfig = config;
    }

    private final EngineConfig mConfig;

    private final Context mContext;

    private final ConcurrentHashMap<AGEventHandler, Integer> mEventHandlerList = new ConcurrentHashMap<>();

    public void addEventHandler(AGEventHandler handler) {
        this.mEventHandlerList.put(handler, 0);
    }

    public void removeEventHandler(AGEventHandler handler) {
        this.mEventHandlerList.remove(handler);
    }

    public void notifyAppLayer(int msg, Object... data) {
        Iterator<AGEventHandler> it = mEventHandlerList.keySet().iterator();
        while (it.hasNext()) {
            AGEventHandler handler = it.next();
            handler.onExtraInfo(msg, data);
        }
    }

    final IRtcEngineEventHandler mRtcEventHandler = new IRtcEngineEventHandler() {
        private final Logger log = LoggerFactory.getLogger(this.getClass());

        @Override
        public void onFirstRemoteVideoDecoded(int uid, int width, int height, int elapsed) {
            log.debug("onFirstRemoteVideoDecoded " + (uid & 0xFFFFFFFFL) + width + " " + height + " " + elapsed);

            Iterator<AGEventHandler> it = mEventHandlerList.keySet().iterator();
            while (it.hasNext()) {
                AGEventHandler handler = it.next();
                handler.onFirstRemoteVideoDecoded(uid, width, height, elapsed);
            }
        }

        @Override
        public void onFirstLocalVideoFrame(int width, int height, int elapsed) {
            log.debug("onFirstLocalVideoFrame " + width + " " + height + " " + elapsed);
        }

        @Override
        public void onUserJoined(int uid, int elapsed) {
        }

        @Override
        public void onUserOffline(int uid, int reason) {
            // FIXME this callback may return times
            Iterator<AGEventHandler> it = mEventHandlerList.keySet().iterator();
            while (it.hasNext()) {
                AGEventHandler handler = it.next();
                handler.onUserOffline(uid, reason);
            }
        }

        @Override
        public void onUserMuteVideo(int uid, boolean muted) {
        }

        @Override
        public void onRtcStats(RtcStats stats) {
        }


        @Override
        public void onLeaveChannel(RtcStats stats) {

        }

        @Override
        public void onLastmileQuality(int quality) {
            log.debug("onLastmileQuality " + quality);
        }

        @Override
        public void onError(int err) {
            super.onError(err);
            log.debug("onError " + err);
        }

        @Override
        public void onJoinChannelSuccess(String channel, int uid, int elapsed) {
            log.debug("onJoinChannelSuccess " + channel + " " + uid + " " + (uid & 0xFFFFFFFFL) + " " + elapsed);

            Iterator<AGEventHandler> it = mEventHandlerList.keySet().iterator();
            while (it.hasNext()) {
                AGEventHandler handler = it.next();
                handler.onJoinChannelSuccess(channel, uid, elapsed);
            }
        }

        public void onRejoinChannelSuccess(String channel, int uid, int elapsed) {
            log.debug("onRejoinChannelSuccess " + channel + " " + uid + " " + elapsed);
        }

        public void onWarning(int warn) {
            log.debug("onWarning " + warn);
        }

    };

    final AgoraAPIOnlySignal.ICallBack mSignalingEventHandler = new AgoraAPIOnlySignal.CallBack() {
        private final Logger log = LoggerFactory.getLogger(this.getClass());

        @Override
        public void onLoginSuccess(int uid, int fd) {
            log.debug("onLoginSuccess " + uid + " " + (uid & 0xFFFFFFFFL) + " " + fd);

        }

        @Override
        public void onLoginFailed(int error) {
            log.debug("onLoginFailed " + error);
        }

        private void doXXWhenDisconnected(int action) {

        }

        @Override
        public void onLogout(int error) {

        }

        @Override
        public void onLog(String txt) {
            log.debug("onLog " + txt);
        }

        @Override
        public void onChannelUserJoined(String account, int uid) {

        }

        @Override
        public void onChannelUserLeaved(String account, int uid) {

        }

        @Override
        public void onChannelUserList(java.lang.String[] accounts, int[] uids) {
            log.debug("onChannelUserList " + Arrays.toString(accounts) + " " + Arrays.toString(uids));

        }

        @Override
        public void onMessageInstantReceive(String account, int uid, String msg) {
            log.debug("onMessageInstantReceive " + account + " " + uid + " " + msg);
        }

        @Override
        public void onMessageChannelReceive(String channel, String account, int uid, String msg) {
            log.debug("onMessageChannelReceive " + channel + " " + account + " " + uid + " " + msg + " " + mConfig.mUid + " " + mConfig.mChannel);
        }
    };


}

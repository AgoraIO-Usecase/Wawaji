package io.agora.wawaji.app.ui;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.SparseBooleanArray;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SurfaceView;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;

import io.agora.common.ToastUtils;
import io.agora.rtc.Constants;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;
import io.agora.wawaji.app.R;
import io.agora.wawaji.app.model.AGEventHandler;
import io.agora.wawaji.app.model.ConstantApp;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.lang.ref.WeakReference;

public class WawajiPlayerActivity extends BaseActivity implements AGEventHandler {

    private final static Logger log = LoggerFactory.getLogger(WawajiPlayerActivity.class);

    private final SparseBooleanArray mUidList = new SparseBooleanArray();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_wawaji_player);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        return false;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return false;
    }

    private boolean isBroadcaster(int cRole) {
        return cRole == Constants.CLIENT_ROLE_BROADCASTER;
    }

    private boolean isBroadcaster() {
        return isBroadcaster(config().mClientRole);
    }

    @Override
    protected void initUIandEvent() {
        event().addEventHandler(this);

        Intent i = getIntent();
        int cRole = i.getIntExtra(ConstantApp.ACTION_KEY_CROLE, 0);

        if (cRole == 0) {
            throw new RuntimeException("Should not reach here");
        }

        String roomName = i.getStringExtra(ConstantApp.ACTION_KEY_ROOM_NAME);

        doConfigEngine(cRole);

        worker().joinChannel(roomName, config().mUid);

        TextView textRoomName = (TextView) findViewById(R.id.room_name);
        textRoomName.setText(roomName);
    }

    private void doConfigEngine(int cRole) {
        SharedPreferences pref = PreferenceManager.getDefaultSharedPreferences(this);
        int prefIndex = pref.getInt(ConstantApp.PrefManager.PREF_PROPERTY_PROFILE_IDX, ConstantApp.DEFAULT_PROFILE_IDX);
        if (prefIndex > ConstantApp.VIDEO_PROFILES.length - 1) {
            prefIndex = ConstantApp.DEFAULT_PROFILE_IDX;
        }
        int vProfile = ConstantApp.VIDEO_PROFILES[prefIndex];

        worker().configEngine(cRole, vProfile);
    }

    @Override
    protected void deInitUIandEvent() {
        doLeaveChannel();
        event().removeEventHandler(this);
    }

    private void doLeaveChannel() {
        worker().leaveChannel(config().mChannel);
        if (isBroadcaster()) {
        }
    }

    public void onLeaveGameClicked(View view) {
        finish();
    }

    @Override
    public void onFirstRemoteVideoDecoded(int uid, int width, int height, int elapsed) {
        doRenderRemoteUi(uid);
    }

    private void doRenderRemoteUi(final int uid) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (isFinishing()) {
                    return;
                }

                if (mUidList.size() >= 1) {
                    return;
                }

                mUidList.put(uid, true);

                doSetupView(uid);
            }
        });
    }

    private void doSetupView(int uid) {
        SurfaceView surfaceV = RtcEngine.CreateRendererView(getApplicationContext());
        surfaceV.setZOrderOnTop(true);
        surfaceV.setZOrderMediaOverlay(true);
        if (config().mUid == uid) {
            return;
        } else {
            rtcEngine().setupRemoteVideo(new VideoCanvas(surfaceV, VideoCanvas.RENDER_MODE_HIDDEN, uid));
        }

        FrameLayout container = (FrameLayout) findViewById(R.id.gaming_video);
        if (container.getChildCount() >= 2) {
            return;
        }
        container.addView(surfaceV);

        config().mWawajiUid = uid;
    }

    private void doRemoveRemoteUi(final int uid) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (isFinishing()) {
                    return;
                }

                rtcEngine().setupRemoteVideo(new VideoCanvas(null, VideoCanvas.RENDER_MODE_HIDDEN, uid));
            }
        });
    }

    @Override
    public void onJoinChannelSuccess(final String channel, final int uid, final int elapsed) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (isFinishing()) {
                    return;
                }

                final boolean isBroadcaster = isBroadcaster();
                log.debug("onJoinChannelSuccess " + channel + " " + (uid & 0xFFFFFFFFL) + " " + elapsed + " " + isBroadcaster);
                worker().getEngineConfig().mUid = uid;
            }
        });
    }

    @Override
    public void onUserOffline(int uid, int reason) {
        log.debug("onUserOffline " + (uid & 0xFFFFFFFFL) + " " + reason);
        doRemoveRemoteUi(uid);
        mUidList.delete(uid);
    }

    public void onCatcherBtnClicked(View view) {
        if (!isBroadcaster()) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }

        ToastUtils.show(new WeakReference<Context>(this) , "请加入控制模块");
    }

    public void onRightBtnClicked(View view) {
        if (!isBroadcaster()) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }

        ToastUtils.show(new WeakReference<Context>(this) , "请加入控制模块");
    }

    public void onDownBtnClicked(View view) {
        if (!isBroadcaster()) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }

        ToastUtils.show(new WeakReference<Context>(this) , "请加入控制模块");
    }

    public void onUpBtnClicked(View view) {
        if (!isBroadcaster()) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }

        ToastUtils.show(new WeakReference<Context>(this) , "请加入控制模块");
    }

    public void onLeftBtnClicked(View view) {
        if (!isBroadcaster()) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }

        ToastUtils.show(new WeakReference<Context>(this) , "请加入控制模块");
    }

    public void onSwitchCameraClicked(View view) {
        if (!isBroadcaster()) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }

        // running on UI thread
        if (mUidList.size() > 1) {
            int targetUid = 0;
            for (int i = 0, size = mUidList.size(); i < size; i++) {
                int uid = mUidList.keyAt(i);
                boolean current = mUidList.get(uid);

                if (current) {
                    mUidList.put(uid, false);
                    if (i < size - 1) {
                        targetUid = mUidList.keyAt(i + 1);
                    } else {
                        targetUid = mUidList.keyAt(0);
                    }
                    break;
                }
            }
            // targetUid should not be 0
            doSetupView(targetUid);
        } else {
            showShortToast(getString(R.string.label_can_not_switch_cam));
        }
    }
}

package io.agora.wawaji.app.ui;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.SparseBooleanArray;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.SurfaceView;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.TextView;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import io.agora.common.Constant;
import io.agora.common.HttpTool;
import io.agora.rtc.Constants;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;
import io.agora.wawaji.app.R;
import io.agora.wawaji.app.model.AGEventHandler;
import io.agora.wawaji.app.model.ConstantApp;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;

public class WawajiPlayerActivity extends BaseActivity implements AGEventHandler {

    private final static Logger log = LoggerFactory.getLogger(WawajiPlayerActivity.class);

    private final SparseBooleanArray mUidList = new SparseBooleanArray();

    private int leyaoyaoRoomid = leyaoyao room id;//you can get it from leyaoyao room list

    private boolean startBtnCanbeClick = true;

    private boolean startBtnControlWawaji = false;

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

        worker().prepareWawaji();

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
        worker().closeWebsocket();

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

                if (uid != Constant.Wawaji_CAM_MAIN && uid != Constant.Wawaji_CAM_SECONDARY) {
                    return;
                }

                boolean isMain = uid == Constant.Wawaji_CAM_MAIN;
                if (isMain) { // always be the main cam
                    doSetupVideoStreamView(uid);
                }

                mUidList.put(uid, isMain);
            }
        });
    }

    private void doSetupVideoStreamView(int uid) {
        SurfaceView surfaceV = RtcEngine.CreateRendererView(getApplicationContext());
        surfaceV.setZOrderOnTop(true);
        surfaceV.setZOrderMediaOverlay(true);
        if (config().mWawajiUid == uid) {
            return;
        } else {
            rtcEngine().setupRemoteVideo(new VideoCanvas(surfaceV, VideoCanvas.RENDER_MODE_HIDDEN, uid));
        }

        FrameLayout container = (FrameLayout) findViewById(R.id.gaming_video);
        if (container.getChildCount() >= 2) {
            return;
        }
        container.removeAllViews();
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

    @Override
    public void onExtraInfo(int msg, Object... data) {
        if (isFinishing()) {
            return;
        }
        int intv;
        boolean boolv;

        switch (msg) {
            case Constant.Wawaji_Msg_TIMEOUT:
                intv = (Integer) data[0];
                startBtnCanbeClick = true;
                startBtnControlWawaji = false;
                break;
            case Constant.Wawaji_Msg_RESULT:
                boolv = (Boolean) data[0];
                if (boolv) {
                    showLongToast("Congrats, lucky day");
                } else {
                    showShortToast("Sorry oops");
                }
                worker().closeWebsocket();
                startBtnCanbeClick = true;
                startBtnControlWawaji = false;
                break;
            case Constant.Wawaji_Msg_FORCED_LOGOUT:
                showShortToast("Forced logout by others " + data[0]);
                startBtnCanbeClick = true;
                startBtnControlWawaji = false;
                break;
            case Constant.Wawaji_Msg_STARTCATCH:
                showShortToast("Start catch wawa");
                startBtnControlWawaji = true;
                break;
        }
    }

    public void onStartBtnClicked(View view) {
        if (startBtnCanbeClick) {
            getWebSocket();
        }

    }

    public void onCatcherBtnClicked(View view) {
        if (!startBtnControlWawaji) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }

        worker().ctrlWawaji(Constant.Wawaji_Ctrl_CATCH);
    }

    public void onRightBtnClicked(View view) {
        if (!startBtnControlWawaji) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }
        view.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_RIGHT);
                        break;
                    case MotionEvent.ACTION_UP:
                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_RIGHT_S);
                        break;
                    default:
                        break;
                }

                return false;
            }
        });
    }

    public void onDownBtnClicked(View view) {
        if (!startBtnControlWawaji) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }
        view.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_DOWN);
                        break;
                    case MotionEvent.ACTION_UP:
                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_DOWN_S);
                        break;
                    default:
                        break;
                }

                return false;
            }
        });
    }

    public void onUpBtnClicked(View view) {
        if (!startBtnControlWawaji) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }
        view.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_UP);
                        break;
                    case MotionEvent.ACTION_UP:
                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_UP_S);
                        break;
                    default:
                        break;
                }

                return false;
            }
        });
    }

    public void onLeftBtnClicked(View view) {
        if (!startBtnControlWawaji) {
            showShortToast(getString(R.string.label_not_a_player));
            return;
        }
        view.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_LEFT);
                        break;
                    case MotionEvent.ACTION_UP:
                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_LEFT_S);
                        break;
                    default:
                        break;
                }

                return false;
            }
        });
    }

    public void onSwitchCameraClicked(View view) {
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
            mUidList.put(targetUid, true);
            // targetUid should not be 0
            doSetupVideoStreamView(targetUid);
        } else {
            showShortToast(getString(R.string.label_can_not_switch_cam));
        }
    }

    private void getWebSocket() {
        if (Constant.BEFIRSTWAWAJI) {
            worker().prepareWawaji();
            startBtnCanbeClick = false;
            new Thread() {
                @Override
                public void run() {
                    super.run();
                    String result = null;
                    try {
                        result = HttpTool.getLeyaoyaoWawajiWebsocket(leyaoyaoRoomid);

                        JsonParser parser = new JsonParser();
                        JsonElement jElem = parser.parse(result);
                        JsonObject obj = jElem.getAsJsonObject();
                        jElem = obj.get("result");

                        int ret = jElem.getAsInt();
                        if (ret == 0) {
                            JsonObject jdata = obj.getAsJsonObject("data");
                            if (!jdata.isJsonNull()) {
                                JsonElement jwsUrl = jdata.get("wsUrl");
                                String wsUrl = jwsUrl.getAsString();
                                Constant.WAWAJI_SERVER_URL = wsUrl;
                                runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        worker().getWebSocket();
                                        worker().ctrlWawaji(Constant.Wawaji_Ctrl_START);
                                    }
                                });
                            }
                        }

                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }.start();

        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        doLeaveChannel();
    }

}

package io.agora.wawaji.app.ui;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.Menu;
import android.view.MenuItem;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.Serializable;

import io.agora.common.Constant;
import io.agora.common.Wawaji;
import io.agora.rtc.Constants;
import io.agora.wawaji.app.R;
import io.agora.wawaji.app.model.AGEventHandler;
import io.agora.wawaji.app.model.ConstantApp;
import io.agora.wawaji.app.model.RomListAdapter;

public class MainActivity extends BaseActivity implements AGEventHandler ,RomListAdapter.onClickButtonInterface {
    private final static Logger log = LoggerFactory.getLogger(MainActivity.class);
    private RecyclerView recyclerView;
    private RomListAdapter romListAdapter;
    private Wawaji[] wawajiArr;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void initUIandEvent() {
        log.debug("initUIandEvent ");
        event().addEventHandler(this);

        recyclerView = (RecyclerView) findViewById(R.id.main_room_recycleview);

        GridLayoutManager layoutManager = new GridLayoutManager(this ,2);
        layoutManager.setOrientation(LinearLayoutManager.VERTICAL);

        recyclerView.setLayoutManager(layoutManager);


    }
    private void refreshRoomView(){
        if (romListAdapter == null){
            romListAdapter = new RomListAdapter(this , wawajiArr ,this);
            //notifyDataSetChanged Prevent picture flicker
            romListAdapter.setHasStableIds(true);
            recyclerView.setAdapter(romListAdapter);

        }else {
            romListAdapter.notifyDataSetChanged();
        }
    }

    @Override
    protected void workerReady() {
        super.workerReady();
        log.debug("workerReady ");

        worker().fetchWawaji();
    }

    @Override
    protected void deInitUIandEvent() {
        event().removeEventHandler(this);
    }


    @Override
    public boolean onCreateOptionsMenu(final Menu menu) {
        return false;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return false;
    }

    public void onRoomBtnClicked(final int position) {
        // show dialog to choose role
     /*   AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(R.string.msg_choose_role);
        builder.setNegativeButton(R.string.label_audience, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                MainActivity.this.forwardToLiveRoom(position ,Constants.CLIENT_ROLE_AUDIENCE);
            }
        });
        builder.setPositiveButton(R.string.label_broadcaster, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                MainActivity.this.forwardToLiveRoom(position ,Constants.CLIENT_ROLE_BROADCASTER);
            }
        });
        AlertDialog dialog = builder.create();

        dialog.show();*/
        forwardToLiveRoom(position ,Constants.CLIENT_ROLE_AUDIENCE);
    }


    public void forwardToLiveRoom(int position ,int cRole) {

        Intent i = new Intent(MainActivity.this, WawajiPlayerActivity.class);
        i.putExtra(ConstantApp.ACTION_KEY_CROLE, cRole);
        i.putExtra(ConstantApp.ACTION_KEY_ROOM_WAWAJI, (Serializable) wawajiArr[position]);

        startActivity(i);
    }

    @Override
    public void onFirstRemoteVideoDecoded(int uid, int width, int height, int elapsed) {

    }

    @Override
    public void onJoinChannelSuccess(String channel, int uid, int elapsed) {

    }

    @Override
    public void onUserOffline(int uid, int reason) {

    }

    @Override
    public void onExtraInfo(final int msg, final Object... data) {
        log.debug("onExtraInfo msg: " + msg + "  data:" + data);
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                switch (msg) {
                    case Constant.APP_Wawaji_Fetch_LIST_RESULT:
                        if (data instanceof Wawaji[]){
                            wawajiArr = (Wawaji[]) data;
                            refreshRoomView();

                        }

                        break;
                }
            }
        });

    }

    @Override
    public void onChannelJoined(String channelID) {

    }

    @Override
    public void onChannelAttrUpdated(String channelID, String name, String value, String type) {

    }

    @Override
    public void onMessageInstantReceive(String account, int uid, String msg) {

    }


    @Override
    public void onItemClickListerner(int position) {
        onRoomBtnClicked(position);
    }
}

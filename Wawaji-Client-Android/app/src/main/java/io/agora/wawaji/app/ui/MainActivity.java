package io.agora.wawaji.app.ui;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import io.agora.common.Constant;
import io.agora.rtc.Constants;
import io.agora.wawaji.app.R;
import io.agora.wawaji.app.model.AGEventHandler;
import io.agora.wawaji.app.model.ConstantApp;

public class MainActivity extends BaseActivity implements AGEventHandler {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void initUIandEvent() {
        EditText textRoomName = (EditText) findViewById(R.id.room_name);
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

        findViewById(R.id.button_join).setEnabled(textRoomName.getText().length() > 4);

        textRoomName.setSelection(textRoomName.getText().length());
    }

    @Override
    protected void workerReady() {
        super.workerReady();

        worker().fetchWawaji();
    }

    @Override
    protected void deInitUIandEvent() {
    }


    @Override
    public boolean onCreateOptionsMenu(final Menu menu) {
        return false;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return false;
    }

    public void onJoinBtnClicked(View view) {
        // show dialog to choose role
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(R.string.msg_choose_role);
        builder.setNegativeButton(R.string.label_audience, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                MainActivity.this.forwardToLiveRoom(Constants.CLIENT_ROLE_AUDIENCE);
            }
        });
        builder.setPositiveButton(R.string.label_broadcaster, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                MainActivity.this.forwardToLiveRoom(Constants.CLIENT_ROLE_BROADCASTER);
            }
        });
        AlertDialog dialog = builder.create();

        dialog.show();
    }

    public void forwardToLiveRoom(int cRole) {
        final EditText v_room = (EditText) findViewById(R.id.room_name);
        String room = v_room.getText().toString();

        Intent i = new Intent(MainActivity.this, WawajiPlayerActivity.class);
        i.putExtra(ConstantApp.ACTION_KEY_CROLE, cRole);
        i.putExtra(ConstantApp.ACTION_KEY_ROOM_NAME, room);

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
    public void onExtraInfo(int msg, Object... data) {
        switch (msg) {
            case Constant.APP_Wawaji_Fetch_LIST_RESULT:
                break;
        }
    }
}

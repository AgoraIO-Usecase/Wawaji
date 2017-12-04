package io.agora.wawaji.app.ui;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.io.IOException;

import io.agora.common.Constant;
import io.agora.common.HttpTool;
import io.agora.common.JsonUtil;
import io.agora.common.LeyaoyaoRoom;
import io.agora.rtc.Constants;
import io.agora.wawaji.app.R;
import io.agora.wawaji.app.model.ConstantApp;

public class MainActivity extends BaseActivity {
    private TextView textViewRoom;
    private String text = "room name:";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (Constant.BEFIRSTWAWAJI) {
            createLeyaoyaoUser();
            getLeyaoyaoRoomlist();
        }

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

        textViewRoom = (TextView) findViewById(R.id.main_roomlist);
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

    private void createLeyaoyaoUser() {
        new Thread() {
            @Override
            public void run() {
                super.run();

                String result = null;
                String resultCent = null;
                try {
                    result = HttpTool.postLeyaoyaoWawajiWS();
                    resultCent = HttpTool.postLeyaoyaoWawajiCharge(100);
                } catch (IOException e) {
                    e.printStackTrace();
                }

                Log.d("MainActivity", "createLeyaoyaoUser:" + result);
                Log.d("MainActivity", "createLeyaoyaoUser resultCent:" + resultCent);

            }
        }.start();

    }

    private void getLeyaoyaoRoomlist() {
        new Thread() {
            @Override
            public void run() {
                super.run();

                String result = null;
                try {
                    result = HttpTool.getLeyaoyaoWawajiRooms();

                    JsonParser parser = new JsonParser();
                    JsonElement jElem = parser.parse(result);
                    JsonObject obj = jElem.getAsJsonObject();
                    jElem = obj.get("result");

                    int ret = jElem.getAsInt();
                    if (ret == 0) {
                        JsonObject jdata = obj.getAsJsonObject("data");
                        if (!jdata.isJsonNull()) {
                            JsonArray machines = jdata.getAsJsonArray("rooms");
                            LeyaoyaoRoom[] rooms = JsonUtil.getGson().fromJson(machines, LeyaoyaoRoom[].class);

                            for (int i = 0; i < rooms.length; i++) {
                                text += "\n" + rooms[i].getId();
                            }

                            runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    textViewRoom.setText(text);
                                }
                            });
                        }

                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }
                Log.d("MainActivity", "getLeyaoyaoRoomlist " + result);

            }
        }.start();
    }
}

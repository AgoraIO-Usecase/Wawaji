package io.agora.common;

import android.content.Context;
import android.media.AudioManager;
import android.media.SoundPool;

import io.agora.wawaji.app.R;

/**
 * Created by yt on 2018/1/4/004.
 */

public class SoundPlayUtils {
    public static SoundPool mSoundPlayer = new SoundPool(10,
            AudioManager.STREAM_MUSIC, 5);
    public static SoundPlayUtils soundPlayUtils;
    static Context mContext;
    private static int soundBackgroundRet = 0;

    /**
     * init
     *
     * @param context
     */
    public static void init(final Context context) {
        if (soundPlayUtils == null) {
            soundPlayUtils = new SoundPlayUtils();
        } else {
            return;
        }

        mContext = context;

        mSoundPlayer.setOnLoadCompleteListener(new SoundPool.OnLoadCompleteListener() {
            @Override
            public void onLoadComplete(SoundPool soundPool, int sampleId, int status) {

            }
        });

        mSoundPlayer.load(mContext, R.raw.background1, 1);// 1
        mSoundPlayer.load(mContext, R.raw.background2, 1);// 2
        mSoundPlayer.load(mContext, R.raw.background3, 1);// 3
        mSoundPlayer.load(mContext, R.raw.catch_failed1, 1);// 4
        mSoundPlayer.load(mContext, R.raw.catch_failed2, 1);// 5
        mSoundPlayer.load(mContext, R.raw.catch_success, 1);// 6
        mSoundPlayer.load(mContext, R.raw.play_game, 1);// 7

    }

    /**
     * play music
     *
     * @param soundID
     */
    public static void play(int soundID) {
        if (soundID == 1 || soundID == 2 || soundID == 3) {
            soundBackgroundRet = mSoundPlayer.play(soundID, 1, 1, 0, -1, 1);

        } else {
            mSoundPlayer.play(soundID, 1, 1, 0, 0, 1);
        }
    }

    public static void stopBackGround() {
        mSoundPlayer.stop(soundBackgroundRet);
    }

}
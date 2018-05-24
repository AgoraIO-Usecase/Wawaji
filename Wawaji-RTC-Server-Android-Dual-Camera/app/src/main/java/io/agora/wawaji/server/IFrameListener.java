package io.agora.wawaji.server;

import io.agora.rtc.video.AgoraVideoFrame;

public interface IFrameListener {
    void onFrameValid(AgoraVideoFrame frame);
}

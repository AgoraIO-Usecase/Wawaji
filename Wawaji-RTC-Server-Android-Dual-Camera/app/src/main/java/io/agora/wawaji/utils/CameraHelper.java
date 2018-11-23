package io.agora.wawaji.utils;

import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.io.IOException;
import java.util.List;

import io.agora.rtc.video.AgoraVideoFrame;
import io.agora.wawaji.server.IFrameListener;

public class CameraHelper implements SurfaceHolder.Callback, Camera.PreviewCallback {
    // default width and height
    private int w = 640;
    private int h = 480;
    private int IMAGE_FORMAT = ImageFormat.NV21;

    private Camera mCamera;
    private IFrameListener mListener;

    public CameraHelper(SurfaceView view, int w, int h, IFrameListener listener) {
        this.w = w;
        this.h = h;

        SurfaceHolder mSurfaceHolder = view.getHolder();
        mSurfaceHolder.setFixedSize(w, h);
        mSurfaceHolder.addCallback(this);
        mSurfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

        mListener = listener;
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        openCamera(holder);
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        releaseCamera();
    }

    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {
        AgoraVideoFrame f = new AgoraVideoFrame();
        f.format = AgoraVideoFrame.FORMAT_NV21;
        f.timeStamp = System.currentTimeMillis();
        f.buf = data;
        f.stride = w;
        f.height = h;
        if (mListener != null)
            mListener.onFrameValid(f);
    }

    private void openCamera(SurfaceHolder holder) {
        releaseCamera(); // release Camera, if not release camera before call camera, it will be locked

        mCamera = Camera.open(Camera.CameraInfo.CAMERA_FACING_BACK); // open default back camera

        mCamera.setErrorCallback(new Camera.ErrorCallback() {
            @Override
            public void onError(int i, Camera camera) {
                String parameters = camera != null ? camera.getParameters().flatten().toString() : "Null Camera";

                Log.i("wawaji", "onError " + i + " " + camera + " " + parameters);
            }
        });

        Camera.Parameters mParams = mCamera.getParameters();

        List<Camera.Size> mParamsSupportedPreviewSizes = mParams.getSupportedPreviewSizes();

        boolean founded = false;
        for (Camera.Size size : mParamsSupportedPreviewSizes) {
            if (size.width == w && size.height == h) {
                founded = true;
                break;
            }
        }
        if (!founded) {
            for (Camera.Size size : mParamsSupportedPreviewSizes) {
                if (size.width == w) {
                    w = size.width;
                    h = size.height;
                    founded = true;
                    break;
                }
            }
        }
        if (!founded) {
            for (Camera.Size size : mParamsSupportedPreviewSizes) {
                if (size.height == h) {
                    w = size.width;
                    h = size.height;
                    founded = true;
                    break;
                }
            }
        }

        if (founded) {
            mParams.setPreviewSize(w, h);
            mParams.setPreviewFormat(IMAGE_FORMAT); // setting preview format：NV21
            mParams.setRotation(0);
            mCamera.setParameters(mParams); // setting camera parameters
            try {
                mCamera.setPreviewDisplay(holder);
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
            mCamera.setPreviewCallback(this);
            mCamera.startPreview();
        }

    }

    private synchronized void releaseCamera() {
        if (mCamera != null) {
            try {
                mCamera.setPreviewCallback(null);
            } catch (Exception e) {
                e.printStackTrace();
            }
            try {
                mCamera.stopPreview();
            } catch (Exception e) {
                e.printStackTrace();
            }
            try {
                mCamera.release();
            } catch (Exception e) {
                e.printStackTrace();
            }
            mCamera = null;
        }
    }

}

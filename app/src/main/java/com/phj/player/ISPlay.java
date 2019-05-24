package com.phj.player;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * 渲染区域
 * Created by phj on 2019/5/3.
 */
public class ISPlay extends GLSurfaceView implements SurfaceHolder.Callback,GLSurfaceView.Renderer {

    public ISPlay(Context context, AttributeSet attrs) {
        super( context,attrs );
        setRenderer(this);
    }


    @Override
    public void surfaceCreated(SurfaceHolder var1){
        initView(var1.getSurface());
        playOrPause();
    }

    @Override
    public void surfaceChanged(SurfaceHolder var1, int var2, int var3, int var4){

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder var1){

    }

    public native void initView(Object surface);

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }

    public native void playOrPause();
}

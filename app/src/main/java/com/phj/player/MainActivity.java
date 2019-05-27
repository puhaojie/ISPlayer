package com.phj.player;

import android.content.pm.ActivityInfo;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.SeekBar;

public class MainActivity extends AppCompatActivity implements Runnable, SeekBar.OnSeekBarChangeListener {

    private static final String TAG = MainActivity.class.getSimpleName();
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private SeekBar seek;
    private ISPlay mISPlay;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.e(TAG, "onCreate: " +(savedInstanceState== null));
        //去掉标题栏
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        //全屏，隐藏状态
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN
        );
        //屏幕为横屏
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        setContentView(R.layout.activity_main);

        Button bt = (Button) findViewById(R.id.open_button);
        seek = (SeekBar) findViewById(R.id.aplayseek);
        mISPlay = (ISPlay) findViewById(R.id.isplay);
        seek.setMax(1000);
        seek.setOnSeekBarChangeListener(this);

        bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mISPlay.open("/sdcard/5.mp4");
            }
        });

        mISPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mISPlay.playOrPause();
            }
        });
        //启动播放进度线程
        Thread th = new Thread(this);
        th.start();
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.e(TAG, "onResume: " );
    }

    @Override
    public void run() {
        for(;;)
        {
            seek.setProgress((int)(mISPlay.playPos()*1000));
            Log.e(TAG, Thread.currentThread()+"run: isPlaying = "+mISPlay.isPlaying() );
            try {
                Thread.sleep( 1000 );
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
        mISPlay.seek( (double)seekBar.getProgress()/(double)seekBar.getMax() );
    }

}

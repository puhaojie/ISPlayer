#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"
#include "IPlayerProxy.h"
#include "XLog.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>

//IVideoView *view;



extern "C"
JNIEXPORT jint
JNI_OnLoad(JavaVM *vm,void* res){

    IPlayerProxy::Get()->Init(vm);
    return JNI_VERSION_1_4;
}


extern "C"
JNIEXPORT jstring
JNICALL
Java_com_phj_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

//    IDemux *de = new FFDemux();
////    de->Open("/sdcard/5.mp4");
//
//    IDecode *vdecode = new FFDecode();
////    vdecode->Open(de->GetVPara(), true);
//
//    IDecode *adecode = new FFDecode();
////    adecode->Open(de->GetAPara());
//
//    // 添加观察者
//    de->AddObs(vdecode);
//    de->AddObs(adecode);
//
//    // 视频转换  并播放
//    view = new GLVideoView();
//    vdecode->AddObs(view);
//
//    // 音频的重采样  并播放
//    IResample *resample = new FFResample();
////    resample->Open(de->GetAPara());
//    adecode->AddObs(resample);
//
//    IAudioPlay *audioPlay = new SLAudioPlay();
//    resample->AddObs(audioPlay);
////    audioPlay->StartPlay(de->GetAPara());
//
//
//
//    IPlayer::Get()->demux = de;
//    IPlayer::Get()->vdecode = vdecode;
//    IPlayer::Get()->adecode = adecode;
//    IPlayer::Get()->videoView = view;
//    IPlayer::Get()->resample = resample;
//    IPlayer::Get()->audioPlay = audioPlay;
//
//    IPlayer::Get()->Open("/sdcard/5.mp4");
//    IPlayer::Get()->Start();

//    de->Start();
//    vdecode->Start();
//    adecode->Start();
//    XSleep(3000);
//    de->Stop();
//    for(;;) {
//        de->Read();
//    }
    return env->NewStringUTF(hello.c_str());
}


extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_ISPlay_playOrPause(JNIEnv *env, jobject instance) {

    IPlayerProxy::Get()->Open("/sdcard/5.mp4");
    IPlayerProxy::Get()->Start();

}

// 初始化窗口
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_ISPlay_initView(JNIEnv *env, jobject instance, jobject surface) {

    //显示窗口初始化
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);
    IPlayerProxy::Get()->InitView(nwin);
}
#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_phj_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IDemux *de = new FFDemux();
    de->Open("/sdcard/5.mp4");

    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode *adecode = new FFDecode();
    adecode->Open(de->GetAPara());

    // 添加观察者
    de->AddObs(vdecode);
    de->AddObs(adecode);

    de->Start();
    vdecode->Start();
    adecode->Start();
//    XSleep(3000);
//    de->Stop();
//    for(;;) {
//        de->Read();
//    }
    return env->NewStringUTF(hello.c_str());
}


// 初始化窗口
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_ISPlay_initView(JNIEnv *env, jobject instance, jobject surface) {

    //显示窗口初始化
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);
    XEGL::Get()->Init(nwin);
    XShader shader;

    shader.Init();

}
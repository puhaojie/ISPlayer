#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "FFDecode.h"

#include "IPlayer.h"
#include "IPlayerProxy.h"

#include <android/native_window.h>
#include <android/native_window_jni.h>





extern "C"
JNIEXPORT jint
JNI_OnLoad(JavaVM *vm,void* res){

    IPlayerProxy::Get()->Init(vm);
    return JNI_VERSION_1_4;
}


// 播放或者暂停
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_ISPlay_playOrPause(JNIEnv *env, jobject instance) {

    IPlayerProxy::Get()->SetPause(!IPlayerProxy::Get()->IsPause());
}

// 初始化窗口
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_ISPlay_initView(JNIEnv *env, jobject instance, jobject surface) {

    //显示窗口初始化
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);
    IPlayerProxy::Get()->InitView(nwin);
}


// 当期播放的时间
extern "C"
JNIEXPORT jdouble JNICALL
Java_com_phj_player_ISPlay_playPos(JNIEnv *env, jobject instance) {

    return IPlayerProxy::Get()->PlayPos();
}

// 播放
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_phj_player_ISPlay_open(JNIEnv *env, jobject instance, jstring path) {
    const char *url = env->GetStringUTFChars(path, 0);

    // TODO
    IPlayerProxy::Get()->Open(url);
    bool re = IPlayerProxy::Get()->Start();

    env->ReleaseStringUTFChars(path, url);
    return (jboolean) re;
}


// 拖拽
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_ISPlay_seek(JNIEnv *env, jobject instance, jlong pos) {
    IPlayerProxy::Get()->Seek(pos);
}

// 是否正在播放
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_phj_player_ISPlay_isPlaying(JNIEnv *env, jobject instance) {
    bool re = IPlayerProxy::Get()->IsPlaying();
    return (jboolean) re;
}


extern "C"
JNIEXPORT jlong JNICALL
Java_com_phj_player_ISPlay_getTotalTime(JNIEnv *env, jobject instance) {


    return IPlayerProxy::Get()->GetTotalTime();

}
#include <jni.h>
#include <string>
#include "FFDemux.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_phj_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IDemux *de = new FFDemux();

    de->Open("/sdcard/5.mp4");
    de->Start();
    XSleep(3000);
    de->Stop();
//    for(;;) {
//        de->Read();
//    }
    return env->NewStringUTF(hello.c_str());
}

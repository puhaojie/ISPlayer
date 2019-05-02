//
// Created by Administrator on 2019/5/2.
//

#ifndef ISPLAYER_XLOG_H
#define ISPLAYER_XLOG_H


class XLog {

};

#ifdef ANDROID
#include <android/log.h>
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"ISPlayNDK",__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,"ISPlayNDK",__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,"ISPlayNDK",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"ISPlayNDK",__VA_ARGS__)

#else
#define LOGD(...) printf("ISPlayNDK",__VA_ARGS__)
#define LOGW(...) printf("ISPlayNDK",__VA_ARGS__)
#define LOGI(...) printf("ISPlayNDK",__VA_ARGS__)
#define LOGE(...) printf("ISPlayNDK",__VA_ARGS__)
#endif

#endif //ISPLAYER_XLOG_H

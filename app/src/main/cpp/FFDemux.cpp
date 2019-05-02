//
// Created by phj on 2019/5/2.
//

#include "FFDemux.h"
#include "XLog.h"

// 因为FFmpeg是用C写入的所以需要加入extern "C"
extern "C" {
#include "libavformat/avformat.h"
}

bool FFDemux::Open(const char *const url) {

    int re = avformat_open_input(&ic, url, 0, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        LOGE("open file %s failed, reason %s ", url, buf);
        return false;
    }

    // 读取文件信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        LOGE("avformat_find_stream_info %s failed, reason %s ", url, buf);
        return false;
    }

    // 尝试获取时间长度
    totalMs = (int) ic->duration / (AV_TIME_BASE / 1000);
    LOGI("totalMs %d", totalMs);

    // 获取音视频的相关信息
    return true;
}


XData FFDemux::Read() {

}


// 构造方法  可在这里做些基本的初始化方法
FFDemux::FFDemux() {
    // 这里不是线程安全的 简单的处理
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;
        //初始化解封装
        av_register_all();
        //初始化网络
        avformat_network_init();
        // 注册所有的解码器
        avcodec_register_all();
        LOGE("register FFmpeg success");
    }
}


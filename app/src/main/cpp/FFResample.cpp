//
// Created by Administrator on 2019/5/7.
//

extern "C"
{
#include <libswresample/swresample.h>
}

#include "XLog.h"
#include <libavcodec/avcodec.h>
#include "FFResample.h"

// 初始化音频上下文
bool FFResample::Open(XParameter in, XParameter out) {
    //音频重采样上下文初始化
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(out.channels),
                              AV_SAMPLE_FMT_S16,out.sample_rate,
                              av_get_default_channel_layout(in.para->channels),
                              (AVSampleFormat)in.para->format,in.para->sample_rate,
                              0,0 );

    int re = swr_init(actx);
    if(re != 0)
    {
        LOGE("swr_init failed!");
        return false;
    }
    else
    {
        LOGI("swr_init success!");
    }
    // 成功了赋值
    outChannels = in.para->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    return true;
}


// 重采样
XData FFResample::Resample(XData indata) {
    return XData();
}

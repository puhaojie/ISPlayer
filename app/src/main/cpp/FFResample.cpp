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
    Close();
    mux.lock();
    //音频重采样上下文初始化
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(out.channels),
                              AV_SAMPLE_FMT_S16,out.sample_rate,
                              av_get_default_channel_layout(in.para->channels),
                              (AVSampleFormat)in.para->format,in.para->sample_rate,
                              0,0 );

    int re = swr_init(actx);
    mux.unlock();
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
    mux.lock();
    // 1、判断indata参数
    if (indata.size <= 0 || !indata.data) {
        mux.unlock();
        return XData();
    }
    if (!actx) {
        mux.unlock();
        return XData();
    }
    AVFrame *frame = (AVFrame *)indata.data;
    // 2、分配copy内存
    XData out;
    // 计算音频大小
    // size = 通道 * 单通道样本数 * 每个样本大小
    int outsize = outChannels * frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat)outFormat);
    if (outsize <= 0) {
        mux.unlock();
        return XData();
    }
    out.Allow(outsize);

    // 定义输出的数组
    uint8_t *outArr[2] = {0};
    outArr[0] = out.data;
    // 开始转换
    // 重采样后的数据存放到 out.data
    int len = swr_convert(actx, outArr, frame->nb_samples, (const uint8_t **) frame->data, frame->nb_samples);
    mux.unlock();
    if (len <= 0) {
        out.Drop();
    }
    out.pts = indata.pts;
//    LOGE("swr_convert success = %d",len);
    return out;
}

void FFResample::Close() {
    mux.lock();
    if(actx)
    {
        swr_free(&actx);
    }
    mux.unlock();
}

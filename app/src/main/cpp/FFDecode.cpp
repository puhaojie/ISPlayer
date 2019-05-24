//
// Created by Administrator on 2019/5/3.
//

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/jni.h>
}
#include "FFDecode.h"
#include "XLog.h"


void FFDecode::InitHard(void *vm) {
    av_jni_set_java_vm(vm,0);
}

bool FFDecode::Open(XParameter para, bool isHard) {

    if (!para.para) return false;
    AVCodecParameters *p = para.para;

    //1、查找解码器
    AVCodec *cd = NULL;

    LOGI("avcodec_find_decoder %d success", p->codec_id);
    if (isHard){
        cd = avcodec_find_decoder_by_name("h264_mediacodec");
        if (!cd) {
            cd = avcodec_find_decoder(p->codec_id);
        }
    } else {
        cd = avcodec_find_decoder(p->codec_id);
    }
    if (!cd) {
        LOGE("avcodec_find_decoder %d failed", p->codec_id);
        return false;
    }
    //2、创建解码上下文
    //解码器初始化
    mux.lock();
    codec = avcodec_alloc_context3(cd);
    // 复制参数
    avcodec_parameters_to_context(codec, p);
    codec->thread_count = 8; //8线程解码

    //打开解码器
    int re = avcodec_open2(codec, 0, 0);
    if (re != 0) {
        mux.unlock();
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf) - 1);
        LOGE("avcodec_open2 failed");
        return false;
    }
    LOGI("avcodec_open2  success；isAudio = %d",1);


    if (codec->codec_type == AVMEDIA_TYPE_VIDEO){
        isAudio = false;
    } else if (codec->codec_type == AVMEDIA_TYPE_AUDIO){
        isAudio = true;
    }

//    LOGI("avcodec_open2  success；isAudio = %d",isAudio);
    mux.unlock();

    return true;
}

bool FFDecode::SendPacket(XData pkt) {

    // 解码器为空或者数据源为空
    if (!codec || pkt.size <= 0 || !pkt.data)
    {
        return false;
    }


    int re = avcodec_send_packet(codec, (const AVPacket *) pkt.data);
    if (re != 0)
    {
        LOGE("avcodec_send_packet failed");
        return false;
    }

    return true;
}

XData FFDecode::RecvFrame() {

    if (!codec)
    {
        return XData();
    }

    if (!frame)
    {
        frame = av_frame_alloc();
    }

    int re = avcodec_receive_frame(codec,frame);
    if (re != 0)
    {
        return XData();
    }

    // 将解码的数据放在XData中存储
    XData d;
    d.data = (unsigned char *) frame;
    // 计算音视频的数据大小
    if (codec->codec_type == AVMEDIA_TYPE_VIDEO){
        d.size = (frame->linesize[0]+frame->linesize[1]+frame->linesize[2])*(frame->height);
        d.width = frame->width;
        d.height = frame ->height;
    } else {
        d.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2; //样本字节数*单通道样本数*通道数
    }

    //
    if (!isAudio) {
        d.format = frame->format;
    }

    pts = frame->pts;
    d.pts = pts;
    // 拷贝解码后的数据
    memcpy(d.datas,frame->data, sizeof(d.datas));
    return d;
}

//
// Created by phj on 2019/5/2.
//

#include "FFDemux.h"
#include "XLog.h"
// 因为FFmpeg是用C写入的所以需要加入extern "C"
extern "C" {
#include "libavformat/avformat.h"
}


//分数转为浮点数
static double r2d(AVRational r)
{
    return r.num == 0 || r.den == 0 ?0.:(double) r.num/(double)r.den;
}



bool FFDemux::Open(const char *const url) {

    Close();
    mux.lock();

    int re = avformat_open_input(&ic, url, 0, 0);
    if (re != 0) {
        mux.unlock();
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        LOGE("open file %s failed, reason %s ", url, buf);
        return false;
    }

    // 读取文件信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0) {
        mux.unlock();
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        LOGE("avformat_find_stream_info %s failed, reason %s ", url, buf);
        return false;
    }

    // 尝试获取时间长度
    totalMs = (int) ic->duration / (AV_TIME_BASE / 1000);
    LOGI("totalMs %d", totalMs);
    mux.unlock();
    // 获取音视频的相关信息
    return true;
}


XData FFDemux::Read() {
    mux.lock();
    if (!ic)
    {
        mux.unlock();
        return XData();
    }

    XData data;
    AVPacket *packet = av_packet_alloc();
    int re = av_read_frame(ic,packet);
    if (re != 0) {
        mux.unlock();
        // 释放空间
        av_packet_free(&packet);
        return XData();
    }

    // 将数据用XData表示 并存储
    data.data = (unsigned char *) packet;
    data.size = packet->size;
//    LOGI("packet size is %d ptts = %lld",packet->size,packet->pts);

    // 需要在XData中保存该数据是音频还是视频帧
    // 解封装时保存  解码的时候使用
    if (packet->stream_index == audioStream){
        data.isAudio = true;
    } else if(packet->stream_index == videoStream){
        data.isAudio = false;
    } else {
        mux.unlock();
        av_packet_free(&packet);
        return XData();
    }
    //转换pts
    packet->pts = (int64_t) (packet->pts * (1000 * r2d(ic->streams[packet->stream_index]->time_base)));
    packet->dts = (int64_t) (packet->dts * (1000 * r2d(ic->streams[packet->stream_index]->time_base)));
    data.pts = (int)packet->pts;
    mux.unlock();
    return data;
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

// 获取视频的解码器参数 AVCodecParameters
// 只有解封装模块中可以获取 即AVFormatContext上下文
XParameter FFDemux::GetVPara() {
    mux.lock();
    if (!ic){
        mux.unlock();
        return XParameter();
    }
    // 获取视频流的索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (re < 0){
        mux.unlock();
        return XParameter();
    }
    LOGI("av_find_best_stream  GetVPara XParameter success %d",re);
    videoStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    mux.unlock();
    return para;
}


// 获取音频的解码器参数 AVCodecParameters
// 只有解封装模块中可以获取 即AVFormatContext上下文
XParameter FFDemux::GetAPara() {
    mux.lock();
    if (!ic){
        mux.unlock();
        return XParameter();
    }
    // 获取音频流的索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (re < 0){
        mux.unlock();
        return XParameter();
    }
    audioStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    para.sample_rate = ic->streams[re]->codecpar->sample_rate;
    para.channels = ic->streams[re]->codecpar->channels;
    mux.unlock();
    return para;
}

/**
 * 关闭清理资源
 */
void FFDemux::Close() {
    mux.lock();
    if (ic){
        avformat_close_input(&ic);
    }
    mux.unlock();
}

bool FFDemux::Seek(double pos) {
    if(pos<0 || pos > 1)
    {
        LOGE("Seek value must 0.0~1.0");
        return false;
    }
    bool re;
    mux.lock();
    if(!ic)
    {
        mux.unlock();
        return false;
    }
    //清理读取的缓冲
    avformat_flush(ic);
    long long seekPts = 0;
    seekPts = ic->streams[videoStream]->duration*pos;

    //往后跳转到关键帧
    re = av_seek_frame(ic,videoStream,seekPts,AVSEEK_FLAG_FRAME|AVSEEK_FLAG_BACKWARD);
    mux.unlock();
    return re;
}


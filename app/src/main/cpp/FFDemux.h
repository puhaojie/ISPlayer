//
// Created by Administrator on 2019/5/2.
//

#ifndef ISPLAYER_FFDEMUX_H
#define ISPLAYER_FFDEMUX_H

#include "IDemux.h"

//因为是指针不用实现，申明即可
struct AVFormatContext;

class FFDemux : public IDemux{
public:
    // 打开相应的流媒体
    virtual bool Open(const char* const url);

    virtual void Close();

    // 解封装后的一帧数据，内存由调用者清理
    virtual XData Read();

    FFDemux();

    // 获取视频参数
    virtual XParameter GetVPara();

    // 获取音频参数
    virtual XParameter GetAPara();

private:
    // 解封装的上下文
    AVFormatContext *ic = 0;

    // todo IObserver中也有 冲突？
    // Open 与 Read会访问ic
    std::mutex mux;

    // 对应的索引
    int audioStream = 1;
    int videoStream = 0;
};


#endif //ISPLAYER_FFDEMUX_H

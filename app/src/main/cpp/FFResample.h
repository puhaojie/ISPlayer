//
// Created by Administrator on 2019/5/7.
//

#ifndef ISPLAYER_FFRESAMPLE_H
#define ISPLAYER_FFRESAMPLE_H

#include "IResample.h"
struct SwrContext;
// FFmpeg 音频重采样类
class FFResample : public IResample{
public:
    virtual bool Open(XParameter in,XParameter out = XParameter());

    // 重采样
    virtual XData Resample(XData indata);
protected:
    SwrContext *actx = 0;
};


#endif //ISPLAYER_FFRESAMPLE_H

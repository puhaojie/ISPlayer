//
// Created by Administrator on 2019/5/18.
//

#ifndef ISPLAYER_SLAUDIOPLAY_H
#define ISPLAYER_SLAUDIOPLAY_H


#include "IAudioPlay.h"

class SLAudioPlay : public IAudioPlay {
public:
    virtual bool StartPlay(XParameter out);
    virtual void Close();
    // 音频数据的入队
    void PlayCall(void *bufq);
    // 分配内存空间
    SLAudioPlay();
    // 清空内存空间
    virtual ~SLAudioPlay();

protected:
    unsigned char *buf = 0;
    std::mutex mux;
};


#endif //ISPLAYER_SLAUDIOPLAY_H

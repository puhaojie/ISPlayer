//
// Created by Administrator on 2019/5/23.
//

#ifndef ISPLAYER_IPLAYER_H
#define ISPLAYER_IPLAYER_H


#include <mutex>
#include "XThread.h"


class IDemux;
class IDecode;
class IResample;
class IVideoView;
class IAudioPlay;


/**
 * IPlayer是播放的接口类，一个对外开放的协议
 */
class IPlayer : public XThread {
public:
    // 单例模式管理
    static IPlayer* Get(unsigned char index = 0);

    // 打开多媒体
    virtual bool Open(const char* path);

    // 开始播放
    virtual bool Start();

    virtual void Close();

    virtual void InitView(void *win);
    IDemux* demux = 0;
    IDecode *vdecode = 0;
    IDecode *adecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;
protected:
    // 用作音视频同步 (采用视频同步音频)
    void Main();
    std::mutex mux;
    IPlayer(){};
};


#endif //ISPLAYER_IPLAYER_H

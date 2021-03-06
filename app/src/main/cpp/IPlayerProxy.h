//
// Created by Administrator on 2019/5/24.
//

#ifndef ISPLAYER_IPLAYERPROXY_H
#define ISPLAYER_IPLAYERPROXY_H

#include <jni.h>
#include "IPlayer.h"

/**
 * 真实的播放类
 */
class IPlayerProxy : public IPlayer {
public:
    static IPlayerProxy *Get()
    {
        static IPlayerProxy px;
        return &px;
    }

    /**
     * 初始化IPlayer对象
     * 并完成硬解码的初始化
     * @param vm javaVM
     */
    void Init(void *vm = 0);
    // 打开多媒体
    virtual bool Open(const char* path);

    // 开始播放
    virtual bool Start();

    virtual void Close();

    virtual bool IsPlaying();

    // 是否正在播放
    virtual long GetTotalTime();

    virtual bool Seek(long pos);

    virtual bool IsPause();

    virtual void SetPause(bool isB);


    virtual void InitView(void *win);

    virtual double PlayPos();

protected:
    IPlayer *iPlayer = 0;
};


#endif //ISPLAYER_IPLAYERPROXY_H

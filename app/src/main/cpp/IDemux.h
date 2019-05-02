//
// Created by Administrator on 2019/5/2.
//
/**
 * 用于实现解封装的接口
 * 目的在于实现解耦
 * 主要作用：解协议和封装，将解析后的数据放到相应的地方解码
 */


#ifndef ISPLAYER_IDEMUX_H
#define ISPLAYER_IDEMUX_H


#include "XData.h"
#include "XThread.h"
#include "IObserver.h"

class IDemux : public IObserver{

public:
    // 打开相应的流媒体
    virtual bool Open(const char* const url) = 0;

    // 解封装后的一帧数据，内存由调用者清理
    virtual XData Read() = 0;

    // 总时长（毫秒级别）
    int totalMs = 0;

protected:
    // 不让用户访问
    virtual void Main();
};


#endif //ISPLAYER_IDEMUX_H

//
// Created by Administrator on 2019/5/18.
//

#ifndef ISPLAYER_IAUDIOPLAY_H
#define ISPLAYER_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver{
public:
    // 接收重采样后的数据  缓冲满之后阻塞
    virtual void Update(XData data);

    //获取缓冲队列，如没有则需要阻塞
    virtual XData GetData();

    virtual bool StartPlay(XParameter out) = 0;
    virtual void Close() = 0;

    // 退出时清空内存空间
    virtual void Clear();
    int maxFrame =100;// 最大缓冲
    // 音频的pts
    int pts = 0;
protected:
    std::list <XData> frames;// 缓冲队列
    std::mutex framesMutex; //音频互斥队列
};



#endif //ISPLAYER_IAUDIOPLAY_H

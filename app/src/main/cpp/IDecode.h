//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_IDECODE_H
#define ISPLAYER_IDECODE_H


#include "IObserver.h"
#include "XParameter.h"
#include "list"

using namespace std;
// 解码接口
// 音频解码和视频解码都用一个接口 需要有isAudio来区分
class IDecode : public IObserver{

public:


    // 打开解码器
    // 默认是非软解码
    virtual bool Open(XParameter parameter,bool isHard = false) = 0;

    virtual void Close() = 0;
    // 将观察者update过来的数据，进行入队。
    // 出队的main中 作为消费 此为消费方法
    virtual bool SendPacket(XData data) = 0;

    // 该方法是解码后的结果
    virtual XData RecvFrame() = 0;

    virtual void Update(XData data);

    int maxList = 200; //最大缓冲队列数量

    // 是否是音频，解码的时候会过滤
    bool isAudio = false;

    // 当前音频播放的时间
    int playPts;
    // 播放渲染的显示时间
    int pts;
protected:
    // 解码的线程的入口
    virtual void Main();

    // 缓冲队列
    std::list<XData> packs;

    // 读取互斥
    std::mutex packsMutex;
};


#endif //ISPLAYER_IDECODE_H

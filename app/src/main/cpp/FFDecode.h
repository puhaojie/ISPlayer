//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_FFDECODE_H
#define ISPLAYER_FFDECODE_H


#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;


class FFDecode : public IDecode {
public:


    // 传递javaVM 初始化硬解码
    static void InitHard(void *vm);

    // 打开解码器
    virtual bool Open(XParameter parameter,bool isHard);

    // 将观察者update过来的数据，进行入队。
    // 出队的main中 作为消费 此为消费方法
    virtual bool SendPacket(XData data);

    // 解封装方法
    virtual XData RecvFrame();

protected:
    std::mutex mux;
    // 解码器
    AVCodecContext *codec  = 0;
    // 解码出的帧数据
    AVFrame *frame = 0;
};


#endif //ISPLAYER_FFDECODE_H

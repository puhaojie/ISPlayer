//
// Created by Administrator on 2019/5/7.
//

#ifndef ISPLAYER_IRESAMPLE_H
#define ISPLAYER_IRESAMPLE_H

#include "IObserver.h"
#include "XParameter.h"

// 音频重采样类
class IResample : public IObserver{

public:
    /**
     * 打开音频上下文
     * @param in 输入参数 （解码时候传入）
     * @param out  （共用户设置的，这里是默认的）
     * @return  成功标志
     */
    virtual bool Open(XParameter in,XParameter out = XParameter()) = 0;

    // 重采样
    virtual XData Resample(XData indata) = 0; // 重采样出来的数据

    // 解码后数据更新后的通知
    virtual void Update(XData data);
    int outChannels = 2;
    int outFormat = 1;
};


#endif //ISPLAYER_IRESAMPLE_H

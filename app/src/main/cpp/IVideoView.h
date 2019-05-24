//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_IVIDEOVIEW_H
#define ISPLAYER_IVIDEOVIEW_H


#include "IObserver.h"

class IVideoView : public IObserver{
public:
    // 保存窗口
    virtual void SetRender(void* win) = 0;

    // 绘制每一帧图像
    virtual void Render(XData data) = 0;

    virtual void Update(XData data);

    virtual void Close() = 0;
};


#endif //ISPLAYER_IVIDEOVIEW_H

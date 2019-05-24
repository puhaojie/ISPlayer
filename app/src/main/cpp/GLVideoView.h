//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_GLVIDEOVIEW_H
#define ISPLAYER_GLVIDEOVIEW_H


#include "XData.h"
#include "IVideoView.h"

class XTexture;

class GLVideoView : public IVideoView{
public:
    // 保存窗口
    virtual void SetRender(void* win);

    // 绘制每一帧图像
    virtual void Render(XData data);

    virtual void Close();
protected:
    std::mutex mux; //互斥变量
    void * view = 0; // 窗体
    XTexture *txt = 0;
};


#endif //ISPLAYER_GLVIDEOVIEW_H

//
// Created by Administrator on 2019/5/3.
//

#include "GLVideoView.h"
#include "XTexture.h"


void GLVideoView::SetRender(void *win) {
    view = win;
}

void GLVideoView::Render(XData data) {
    // 绘制
    if (!view)
        return;

    // 第一次初始化XTexture
    if (!txt) {
        txt = XTexture::Create();;
        txt->Init(view,(XTextureType) data.format);
    }


    // 每一帧都在这里面渲染
    txt->Draw(data.datas,data.width,data.height);
}

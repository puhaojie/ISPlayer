//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_XEGL_H
#define ISPLAYER_XEGL_H


#include <mutex>

class XEGL
{
public:
    // 初始化窗口
    virtual bool Init(void *win) = 0;
    virtual void Close() = 0;
    static XEGL *Get();
    virtual void Draw() = 0;


protected:
    // 构造方法不对外开放
    XEGL(){}
    std::mutex mux;
};


#endif //ISPLAYER_XEGL_H

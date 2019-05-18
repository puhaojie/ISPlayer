//
// Created by Administrator on 2019/5/18.
//

#include "IAudioPlay.h"
#include "XLog.h"


// 生产者  只需要压队  不需要对数据处理
void IAudioPlay::Update(XData data) {

    if (data.size <= 0 || !data.data) {
        return;
    }
    // 没退出循环
    while (!isExit) {
        framesMutex.lock();
        if(frames.size() > maxFrame)
        {
            framesMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        framesMutex.unlock();
        // 释放CPU
        XSleep(1);
        return;
    }
}


// 消费者，用于重采样后数据的显示
XData IAudioPlay::GetData()
{
    XData d;

    isRunning = true;
    while(!isExit)
    {

        framesMutex.lock();
        if(!frames.empty())
        {
            LOGE("GetData %d",frames.size());
            d = frames.front();
            frames.pop_front();
            framesMutex.unlock();
            pts = d.pts;
            return d;
        }
        framesMutex.unlock();
        XSleep(1);
    }
    isRunning = false;
    return d;
}


void IAudioPlay::Clear() {
    framesMutex.lock();

    // 出队并释放内存
    if (!frames.empty())
    {
        frames.front().Drop();
        frames.pop_front();
    }

    framesMutex.unlock();
}



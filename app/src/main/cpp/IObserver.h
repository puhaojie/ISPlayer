//
// Created by Administrator on 2019/5/2.
//

#ifndef ISPLAYER_IOBSERVER_H
#define ISPLAYER_IOBSERVER_H

#include "XThread.h"
#include "vector"
#include "mutex"
#include "XData.h"

using namespace std;

// 作为观察者 来达到通知的作用

class IObserver : public XThread {
public:
    // 更新
    virtual void Update(XData data) {};

    // 增加一个观察者
    virtual void AddObs(IObserver *obs);

    // 通知给相应的观察者
    virtual void Notify(XData data);

protected:
    std::vector<IObserver *> obss;//集合对象

    std::mutex mux;
};


#endif //ISPLAYER_IOBSERVER_H

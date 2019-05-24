//
// Created by Administrator on 2019/5/24.
//

#include "IPlayerProxy.h"
#include "FFPlayerBuilder.h"
#include "XLog.h"

// 初始化硬解码及构建播放器引擎
void IPlayerProxy::Init(void *vm) {
    mux.lock();
    if (vm) {
        FFPlayerBuilder::InitHard(vm);
    }
    if (!iPlayer)
        iPlayer = FFPlayerBuilder::Get()->BuilderPlayer();

    mux.unlock();
}

bool IPlayerProxy::Open(const char *path) {
    mux.lock();
    bool re = false;
    if (iPlayer) {
        re = iPlayer->Open(path);
    }
    mux.unlock();
    return re;
}

bool IPlayerProxy::Start() {
    mux.lock();
    bool re = false;
    if (iPlayer) {
        re = iPlayer->Start();
    }
    mux.unlock();
    return re;
}

void IPlayerProxy::InitView(void *win) {
    mux.lock();

    if (iPlayer)
    {
        iPlayer->InitView(win);
    }
    mux.unlock();
}

void IPlayerProxy::Close() {
    mux.lock();

    if (iPlayer)
    {
        iPlayer->Close();
    }
    mux.unlock();
}

//
// Created by Administrator on 2019/5/2.
//


#include "XThread.h"
#include "thread"
#include "XLog.h"

using namespace std;


// 毫秒级别的sleep
void XSleep(int mis) {
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}


bool XThread::Start() {
    isExit = false;
    isPause = false;
    // 创建一个线程
    thread th(&XThread::ThreadMain, this);
    th.detach();//放弃对线程的控制
    return true;
}

void XThread::ThreadMain() {
    isRunning = true;
    LOGI("线程函数进入");
    Main();
    LOGI("线程函数退出");
    isRunning = false;
}

void XThread::Stop() {
    isExit = true;
    for (int i = 0; i < 100; ++i) {
        if (!isRunning){
            LOGI("停止线程成功");
            return;
        }
        XSleep(1);
    }
    LOGI("停止线程超时");
}

void XThread::SetPause(bool isP) {
    isPause = isP;
    for (int i = 0; i < 10; ++i) {
        if (isP == isPausing) {
            break;
        }
        XSleep(10);
    }
}

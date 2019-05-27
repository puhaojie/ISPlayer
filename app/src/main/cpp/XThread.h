//
// Created by phj on 2019/5/2.
//
//

#ifndef ISPLAYER_XTHREAD_H
#define ISPLAYER_XTHREAD_H

void XSleep(int mis);

class XThread {

public:
    // 启动线程（外部进入的方法） 代表线程读取工作的启动
    virtual bool Start();

    // 设置暂停还是播放
    virtual void SetPause(bool isP);

    // 判断是否暂停
    virtual bool IsPause()
    {
        isPausing = isPause;
        return isPause;
    }

    // 安全停止
    virtual void Stop();

    // 入口主函数
    virtual void Main(){}

protected:
    bool isRunning = false;//是否正在运行
    bool isExit = false;//是否停止
    bool isPause = false;
    bool isPausing = false;

private:
    void ThreadMain();
};


#endif //ISPLAYER_XTHREAD_H

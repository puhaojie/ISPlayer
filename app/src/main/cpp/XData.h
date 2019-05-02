//
// Created by Administrator on 2019/5/2.
//

#ifndef ISPLAYER_XDATA_H
#define ISPLAYER_XDATA_H

enum XDataType // 涉及到释放内存的问题
{
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1
};

struct XData {

    // 清理的问题，关于哪一种类型
    int type = 0;

    unsigned char* data = 0;

    int size = 0;

    // 清理
    void Drop();

};


#endif //ISPLAYER_XDATA_H

//
// Created by Administrator on 2019/5/2.
//

#include "XData.h"
extern "C"{
#include <libavformat/avformat.h>
}

// 清理工作
void XData::Drop() {

    if (!data)
    {
        return;
    }

    if (type == AVPACKET_TYPE)
    {
        av_packet_free((AVPacket **) &data);
    } else
    {
        delete data;
    }

    data = 0;
    size = 0;
}


// 分配一定的内存空间
bool XData::Allow(int size, const char *d) {
    Drop();
    type = UCHAR_TYPE;
    if (size<=0)
        return false;
    this->data = new unsigned char[size];

    if (!this->data)
        return false;

    // 分配成功再copy
    if (d) {
        memcpy(this->data,d,size);
    }
    this->size = size;
    return true;
}

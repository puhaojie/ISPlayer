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
    } else {
        delete data;
    }

    data = 0;
    size = 0;
}

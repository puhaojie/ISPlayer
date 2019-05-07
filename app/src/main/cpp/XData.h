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

// 该数据是存储解封装后的数据 以及解码后的数据
struct XData {

    // 清理的问题，关于哪一种类型，是否是FFmpeg
    int type = 0;
    // 该数据是存储解封装后的数据||解码后的数据
    unsigned char* data = 0;

    // 解码后的数据
    unsigned char* datas[8] = {0};

    int size = 0;

    // 清理
    void Drop();

    // 视频的宽和高
    int width;
    int height;
    bool isAudio = false; // 是否是音频流
};


#endif //ISPLAYER_XDATA_H

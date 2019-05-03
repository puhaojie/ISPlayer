//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_XPARAMETER_H
#define ISPLAYER_XPARAMETER_H


struct AVCodecParameters;

//解码器的存储
class XParameter {

public:
    AVCodecParameters *para = 0;
    int sample_rate = 44100;
    int channels = 2;
};


#endif //ISPLAYER_XPARAMETER_H

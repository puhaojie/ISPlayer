//
// Created by Administrator on 2019/5/24.
//

#ifndef ISPLAYER_FFPLAYERBUILDER_H
#define ISPLAYER_FFPLAYERBUILDER_H


#include "IPlayerBuilder.h"

class FFPlayerBuilder: public IPlayerBuilder {
public:
    static void InitHard(void *vm);

    static FFPlayerBuilder* Get() {
        static FFPlayerBuilder ff;
        return &ff;
    }

protected:
    virtual IDemux* CreateDemux();
    virtual IDecode* CreateDecode();
    virtual IResample* CreateResample();
    virtual IVideoView* CreateVideoView();
    virtual IAudioPlay* CreateAudioPlay();
    virtual IPlayer* CreatePlayer(unsigned char index = 0);
};


#endif //ISPLAYER_FFPLAYERBUILDER_H

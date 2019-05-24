//
// Created by Administrator on 2019/5/24.
//

#ifndef ISPLAYER_IPLAYERBUILDER_H
#define ISPLAYER_IPLAYERBUILDER_H

#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IVideoView.h"
#include "IAudioPlay.h"
#include "IPlayer.h"

/**
 * 播放器的builder
 * 用于构建对应的组件，并且拼装
 */
class IPlayerBuilder {
public:
    // 用于组装
    virtual IPlayer *BuilderPlayer(unsigned char index=0);

protected:
    virtual IDemux* CreateDemux() = 0;
    virtual IDecode* CreateDecode() = 0;
    virtual IResample* CreateResample() = 0;
    virtual IVideoView* CreateVideoView() = 0;
    virtual IAudioPlay* CreateAudioPlay() = 0;
    virtual IPlayer* CreatePlayer(unsigned char index = 0) = 0;

};


#endif //ISPLAYER_IPLAYERBUILDER_H

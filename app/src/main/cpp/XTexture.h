//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_XTEXTURE_H
#define ISPLAYER_XTEXTURE_H

//存储格式不同会导致解码的方式也不同
enum XTextureType { // 存储格式问题
    XTEXTURE_YUV420P = 0,// Y 4 U 1 V 1
    XTEXTURE_NV12 = 25, // Y 4 UV 1
    XTEXTURE_NV21 = 26  // Y 4 VU 1
};


class XTexture {

public:
    // void* 方式可以存放任何格式的对象 相当于java中的object

    // 初始化（XEGL和XShader）
    virtual bool Init(void *win) = 0;

    static XTexture* Create();

    // 绘制每一帧数据
    // 数据 和 视频宽高
    virtual void Draw(unsigned char* data[],int width,int height) = 0;
};


#endif //ISPLAYER_XTEXTURE_H

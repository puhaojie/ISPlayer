//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_XSHADER_H
#define ISPLAYER_XSHADER_H

#include <mutex>

enum XShaderType {
    XSHADER_YUV420P =0,// Y 4 U 1 V 1
    XSHADER_NV12 = 25, // Y 4 UV 1
    XSHADER_NV21 = 26  // Y 4 VU 1
};
// 材质的绘制
class XShader {
public:
    // 初始化
    virtual bool Init(XShaderType type = XSHADER_YUV420P);

    virtual void Close();
    /**
     * 获取材质 并映射到内存
     * @param index 层级第几层数据
     * @param width 宽
     * @param height 高
     * @param buf  数据
     */
    virtual void GetTexture(unsigned int index,int width,int height,unsigned char* buf,bool isa = false);

    virtual void Draw();

protected:
    // 顶点和片元Shader 全局变量用于清理
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int texts[100] = {0}; //材质
    // 渲染
    unsigned int program = 0;
    //
    std::mutex mux;
};


#endif //ISPLAYER_XSHADER_H

//
// Created by Administrator on 2019/5/3.
//

#ifndef ISPLAYER_XSHADER_H
#define ISPLAYER_XSHADER_H


// 材质的绘制
class XShader {
public:
    virtual bool Init();

protected:
    // 顶点和片元Shader 全局变量用于清理
    unsigned int vsh = 0;
    unsigned int fsh = 0;

    // 渲染
    unsigned int program = 0;
};


#endif //ISPLAYER_XSHADER_H

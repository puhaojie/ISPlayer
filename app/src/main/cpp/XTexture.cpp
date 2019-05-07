//
// Created by Administrator on 2019/5/3.
//

#include "XTexture.h"
#include "XEGL.h"
#include "XShader.h"


class CXTexture : public XTexture {
public:
    // XShader应该是独此一份 需要保存 做后续的处理
    XShader sh;

    virtual bool Init(void* win) {

        if (!win) {
            return false;
        }

        if (!XEGL::Get()->Init(win)) {
            return false;
        }

        sh.Init();

        return true;
    }



    virtual void Draw(unsigned char* data[],int width,int height) {
        sh.GetTexture(0, width, height, data[0]); // y
        sh.GetTexture(1, width / 2, height / 2, data[1]); // u
        sh.GetTexture(2, width / 2, height / 2, data[2]); // v

        sh.Draw();

        XEGL::Get()->Draw();
    }

};

XTexture *XTexture::Create() {
    return new CXTexture();
}

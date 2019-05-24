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
    // GetTexture时候使用
    XTextureType type;


    virtual void Drop()
    {
        mux.lock();
        XEGL::Get()->Close();
        sh.Close();
        mux.unlock();
        delete this;
    }


    virtual bool Init(void *win, XTextureType type) {
        XEGL::Get()->Close();
        mux.lock();
        this->type = type;
        if (!win) {
            mux.unlock();
            return false;
        }

        if (!XEGL::Get()->Init(win)) {
            mux.unlock();
            return false;
        }

        sh.Init((XShaderType) type);
        mux.unlock();

        return true;
    }


    virtual void Draw(unsigned char *data[], int width, int height) {
        mux.lock();
        sh.GetTexture(0, width, height, data[0]); // y

        if (type == XTEXTURE_YUV420P) {
            sh.GetTexture(1, width / 2, height / 2, data[1]); // u
            sh.GetTexture(2, width / 2, height / 2, data[2]); // v
        } else {
            sh.GetTexture(1, width / 2, height / 2, data[1], true); // u
        }


        sh.Draw();

        XEGL::Get()->Draw();
        mux.unlock();
    }

};

XTexture *XTexture::Create() {
    return new CXTexture();
}

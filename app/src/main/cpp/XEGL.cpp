//
// Created by Administrator on 2019/5/3.
//

#include <android/native_window.h>
#include "XEGL.h"
#include "EGL/egl.h"
#include "XLog.h"


// 将CXEGL的申明和继承放在一起
class CXEGL : public XEGL {

public:

    // 成员变量（保存是为了便于销毁）
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    // 初始化
    virtual bool Init(void *win) {
        ANativeWindow *nwin = (ANativeWindow *) win;


        // 1、获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY)
        {
            return false;
        }

        // 2、初始化display对象
        int re = eglInitialize(display,0,0);
        if (re != EGL_TRUE) {
            return false;
        }


        // 3、获取配置 并创建Surface
        EGLint configSpec[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE // 数组末尾标志
        };

        // 获取配置
        EGLConfig config = 0;
        // 获取数量
        EGLint numConfigs = 0;
        re = eglChooseConfig(display,configSpec,&config,1,&numConfigs);
        if (re != EGL_TRUE) {
            return false;
        }
        // 外部的窗口和OpenGL关联
        surface = eglCreateWindowSurface(display, config, nwin,NULL);

        // 4、创建EGL上下文并打开
        const EGLint ctxAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
        if (context == EGL_NO_CONTEXT) {
            return false;
        }
        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            return false;
        }
        LOGI("CXEGL Init success");
        return true;
    }


    virtual void Close() {

    }
};

// 单例模式
XEGL *XEGL::Get() {
    static CXEGL xegl;
    return &xegl;
}

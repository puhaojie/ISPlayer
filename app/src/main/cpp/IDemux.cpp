//
// Created by Administrator on 2019/5/2.
//

#include "IDemux.h"

void IDemux::Main() {

    while (!isExit) {

        XData data = Read();
        if (data.size > 0)
        {
            Notify(data);
        }
        else
        {
            XSleep(2);
        }
    }

}

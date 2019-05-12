//
// Created by Administrator on 2019/5/7.
//

#include "IResample.h"

void IResample::Update(XData data) {
    XData d = this->Resample(data);
    if(d.size > 0)
    {
        this->Notify(d);
    }
}

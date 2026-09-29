//
// Created by 铲 on 2026/9/23.
//

#ifndef 生态系统模拟系统_SMALLFISH_H
#define 生态系统模拟系统_SMALLFISH_H

#include "Fish.h"
class smallFish:public Fish
{
    public:
    smallFish(int x, int y  );
    void update() override;
};


#endif //生态系统模拟系统_SMALLFISH_H

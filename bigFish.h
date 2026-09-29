//
// Created by 铲 on 2026/9/23.
//

#ifndef 生态系统模拟系统_BIGFISH_H
#define 生态系统模拟系统_BIGFISH_H
#include "Fish.h"

class bigFish:public Fish
{
    public:
    bigFish(int x, int y);
    void update() override;

};


#endif //生态系统模拟系统_BIGFISH_H

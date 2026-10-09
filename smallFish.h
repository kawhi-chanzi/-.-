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

    // ============ 猎物相关的覆写 ============
    // 小鱼被吃掉时，能给捕食者提供多少能量（固定 3 点）。
    // 返回值大于 0，大鱼才知道"这东西能吃"。
    int foodValue() const override;
    // 地图上的代号，用小写 s 表示小鱼（small）
    char symbol() const override;
    // 播报事件时显示的名字
    std::string name() const override;
};


#endif //生态系统模拟系统_SMALLFISH_H
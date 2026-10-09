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

    // ============ 捕食者相关的覆写 ============
    // 尝试吃掉 other：吃到返回 true，够不着或者不能吃返回 false
    bool tryEat(Organism* other) override;
    // 地图上的代号，用大写 B 表示大鱼（Big）
    char symbol() const override;
    // 播报事件时显示的名字
    std::string name() const override;
};


#endif //生态系统模拟系统_BIGFISH_H
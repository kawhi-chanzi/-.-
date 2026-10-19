//
// Created by 铲 on 2026/10/14.
//

#ifndef 类图_PUML_WOLF_H
#define 类图_PUML_WOLF_H
#include "Organism.h"

// 狼：住在陆地上的生物。
// x/y/speed/energy 和 getX/getY 都不用自己写了——这些已经上提到基类 Organism；
// 移动逻辑（含"这格能不能进"的地形判定）也整段在 Organism::update() 里实现。
// 所以 wolf 现在只需要做一件事：声明"我住在陆地"。
class wolf: public Organism
{
public:
    wolf(int life,int x, int y,int speed, int energy);

    // 狼没有额外的行为，走基类的"耗能量 + 地形判定移动"即可
    virtual void update(World* world) override;

    // 栖息地：'#' 表示陆地。基类默认是 '.'（水），这里覆写成陆地。
    // 这个值会被基类 update() 拿去和 World 的地形比对：
    // 只有目标格是 '#' 时狼才走得过去，踩到水就原地不动。
    char habitat() const override{ return '#'; }

    // 地图上的代号和播报事件时用的名字
    char symbol() const override{ return 'W'; }
    std::string name() const override{ return "狼"; }
};


#endif //类图_PUML_WOLF_H

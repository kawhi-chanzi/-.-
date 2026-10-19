//
// Created by 铲 on 2026/9/21.
//

#include "Fish.h"

// 构造函数的活儿交给基类：生命的初始化（alive/age/age_max）和
// 位置移动相关的成员（x/y/speed/energy）现在都统一由 Organism 负责。
Fish::Fish(int life,int x, int y, int speed,int energy)
: Organism(life, x, y, speed, energy) {}

void Fish::update(World* world)
{
    // 鱼自己暂时没有额外的行为，移动（含地形判定）在基类里统一实现
    Organism::update(world);
}

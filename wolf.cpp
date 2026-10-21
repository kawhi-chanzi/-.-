//
// Created by 铲 on 2026/10/14.
//

#include "wolf.h"

// 构造函数同样把活儿交给基类：生命相关和位置移动相关的成员都由 Organism 初始化
wolf::wolf(int x, int y)
: Organism(40, x, y, 1, 30) {}

void wolf::update(World* world)
{
    // 狼的移动（含"脚下这格是不是陆地"的判定）都在基类 Organism::update() 里，
    // 所以这里只做转发。
    Organism::update(world);
}

char wolf::habitat() const
{
    return '#';
}

std::string wolf::name() const
{
    return "狼";
}
char wolf::symbol() const
{
    return 'W';
}
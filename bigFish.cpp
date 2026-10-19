//
// Created by 铲 on 2026/9/23.
//

#include "bigFish.h"

#include <algorithm>   // std::max 需要它
#include <cstdlib>     // std::abs 需要它

// 大鱼：寿命 35、速度 2、初始能量 25。
// 说明：初始能量由原来的 35 调小到 25。
// 每走一步消耗 1 点能量（不管这一步实际走了几格），
// 所以不捕食的话，25 步内能量耗尽就会饿死。
// 大鱼靠 tryEat 捕食小鱼补充能量（每吃一条 +3），
// 吃得够勤就能一直活到寿命上限 35 才自然老死。
bigFish::bigFish(int x,int y):Fish(35,x,y,2,25){}

void bigFish::update(World* world)
{
    // 大鱼暂时没有额外的行为，直接复用 Fish 的游动逻辑
    Fish::update(world);
}

bool bigFish::tryEat(Organism* other)
{
    // 自己已经死了（比如这一步刚饿死），就什么也做不了
    if (alive == false)
    {
        return false;
    }

    // other 是空指针、或者对方已经死了，都不能吃
    if (other == nullptr || other->isAlive() == false)
    {
        return false;
    }

    // foodValue() 表示"对方被吃掉时能给多少能量"，返回 0 说明这东西不能吃。
    // 小鱼覆写后返回 3；大鱼自己不覆写、用基类默认值 0。
    // 所以这一句同时排除了"吃大鱼"和"吃自己"两种情况。
    int food = other->foodValue();
    if (food <= 0)
    {
        return false;
    }

    // 判断够不够得着：用切比雪夫距离，也就是横、纵坐标差值的最大者。
    // 距离 <= 1 就算"挨着"，才咬得到（含正上、正下、左右和四个斜角）。
    int dx = std::abs(x - other->getX());
    int dy = std::abs(y - other->getY());
    int distance = std::max(dx, dy);
    if (distance > 1)
    {
        return false;
    }

    // 咬死猎物
    other->kill();

    // 吃掉后恢复固定能量：猎物的 foodValue 就是那个固定值（小鱼 = 3）
    energy += food;

    return true;
}

char bigFish::symbol() const
{
    return 'B';
}

std::string bigFish::name() const
{
    return "大鱼";
}
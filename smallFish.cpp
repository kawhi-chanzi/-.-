//
// Created by 铲 on 2026/9/23.
//

#include "smallFish.h"

// 小鱼：寿命 30、速度 1、初始能量 30。
// 同理，初始能量由原来的 5 调大到 30（与寿命相当），
// 这样小鱼不会再因为能量见底而在几天内全部饿死，
// 整个种群能稳定维持下去，把戏份留给"被大鱼捕食"这条主线。
smallFish::smallFish(int x,int y):Fish(30,x,y,1,30)
{}

void smallFish::update()
{
    // 小鱼暂时没有额外的行为，直接复用 Fish 的游动逻辑
    Fish::update();
}

int smallFish::foodValue() const
{
    // 固定值：大鱼每吃掉一条小鱼，恢复 3 点能量
    return 3;
}

char smallFish::symbol() const
{
    return 's';
}

std::string smallFish::name() const
{
    return "小鱼";
}
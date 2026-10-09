//
// Created by 铲 on 2026/9/21.
//
#include <iostream>

#include <cstdlib>   // srand 需要它
#include <ctime>     // time 需要它

#include "World.h"

using namespace std;

int main() {
    // 用当前时间做随机种子，这样每次运行鱼的游动路线都不一样
    srand((unsigned)time(0));

    World world;

    // 往水里放鱼。想加鱼就照这样继续写 addCreature。
    // 大鱼 'B' 是捕食者，小鱼 's' 是猎物。
    world.addCreature(new bigFish(2, 2));
    world.addCreature(new bigFish(17, 8));
    world.addCreature(new smallFish(1, 1));
    world.addCreature(new smallFish(5, 3));
    world.addCreature(new smallFish(8, 4));
    world.addCreature(new smallFish(12, 2));
    world.addCreature(new smallFish(15, 7));

    // 模拟 10 天，每天 World::STEPS_PER_DAY（=3）步。
    // 每一步发生的事件、以及每天结束时的地图和存活数量，
    // 都由 World::step() 内部自动打印，这里不用再管。
    for (int i = 0; i < 10; i++)
    {
        for (int s = 0; s < World::STEPS_PER_DAY; s++)
        {
            world.step();
        }
    }

    return 0;
}
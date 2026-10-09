//
// Created by 铲 on 2026/9/21.
//
#include <iostream>

#include <cstdlib>   // srand 需要它
#include <ctime>     // time 需要它

#ifdef _WIN32
// windows.h 默认会定义 min/max 两个宏，可能和标准库的 std::max 冲突，
// 所以先定义 NOMINMAX 把它关掉（MinGW 的头文件里已经定义过，这里加个保护避免重复定义）
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>   // 只为了下面切换控制台代码页的两个函数，其他系统用不到
#endif

#include "World.h"

using namespace std;

int main() {
#ifdef _WIN32
    // Windows 控制台默认按 GBK(936) 代码页显示，而本程序输出的是 UTF-8 字节，
    // 两边对不上，中文就会显示成乱码。
    // 这里把控制台的输出、输入代码页都切成 UTF-8，从根上解决乱码。
    // 好处：不管是直接在 cmd / PowerShell 里运行，还是从 CLion 里运行，
    // 都不需要手动敲 chcp 65001，也不用去改 IDE 的编码设置。
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

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
//
// Created by 铲 on 2026/9/23.
//

#include "World.h"

#include <iostream>

#include "Organism.h"
using namespace std;

World::World()
    : day(1), stepInDay(0)
{
}

World::~World()
{
    // 修复内存泄漏：creatures 里存的全是 new 出来的对象，
    // World 销毁时必须负责把它们全部 delete 掉。
    // 注意：死掉的生物已经在 removeDead() 里删过了，所以容器里剩下的都是还活着的。
    for (auto c : creatures)
    {
        delete c;
    }
    creatures.clear();
}

void World::addCreature(Organism* c)
{
    creatures.push_back(c);
}

void World::step()
{
    // 1) 让每个还活着的生物走一步（移动、消耗能量、按年龄判断生死）。
    //    update 之前还活着、之后却死了，说明是自然死亡（老死或者饿死），顺手记成事件。
    for (auto c : creatures)
    {
        if (c->isAlive() == true)
        {
            c->update();

            if (c->isAlive() == false)
            {
                dayEvents.push_back(c->name() + "(" + to_string(c->getX()) + "," + to_string(c->getY()) + ") 死亡");
            }
        }
    }

    // 2) 捕食判定：等所有生物都移动完了，再统一判断谁吃了谁。
    //    这样做是为了避免"谁先被遍历到谁就占便宜"这种顺序上的不公平。
    //    这里对每个生物都调用 tryEat，但只有大鱼会真的吃——
    //    其他生物用的是基类的默认实现，永远返回 false。
    for (auto eater : creatures)
    {
        if (eater->isAlive() == false)
        {
            continue;
        }

        for (auto other : creatures)
        {
            if (eater == other)
            {
                continue;   // 不能吃自己
            }

            if (eater->tryEat(other) == true)
            {
                // 捕到食物了，记一条事件。
                // 这里读的是被吃之前的坐标：removeDead() 还没执行，猎物对象还在内存里，
                // 坐标依然读得到。
                dayEvents.push_back(eater->name() + "(" + to_string(eater->getX()) + "," + to_string(eater->getY())
                                    + ") 吃掉了 " + other->name() + "(" + to_string(other->getX()) + "," + to_string(other->getY()) + ")");
            }
        }
    }

    // 3) 清理这一步死掉的生物（被吃掉的、饿死的、老死的），同时释放它们的内存
    removeDead();

    // 4) 步数 +1
    stepInDay++;

    // 5) 事件"有才汇报"：这一步确实发生了事情才打印，没事件就静悄悄地过去
    reportEvents();

    // 6) 每天汇报：走满 STEPS_PER_DAY 步就算过完一天，打印地图和存活情况
    if (stepInDay >= STEPS_PER_DAY)
    {
        show();
        stepInDay = 0;
        day++;
    }
}

void World::removeDead()
{
    // 用迭代器遍历：erase 之后会让 it 指向下一个有效位置，
    // 所以不能写成普通的 for 或者范围 for（那样删元素时迭代器会失效）。
    for (auto it = creatures.begin(); it != creatures.end(); )
    {
        if ((*it)->isAlive() == false)
        {
            delete *it;                 // 先释放内存，不然对象没了、指针还在，内存就泄漏了
            it = creatures.erase(it);   // 再从容器里摘掉这个指针
        }
        else
        {
            ++it;
        }
    }
}

void World::reportEvents()
{
    // 没事件就直接返回，什么都不打印——这就是"有才汇报"
    if (dayEvents.empty() == true)
    {
        return;
    }

    cout << "【第 " << day << " 天 · 第 " << stepInDay << " 步】发生的事件:" << endl;
    for (const auto& event : dayEvents)
    {
        cout << "    " << event << endl;
    }

    dayEvents.clear();   // 播报完就清空，免得下一天又重复打印一遍
}

void World::show()
{
    // 1) 先准备一张字符地图，全部填成水域符号 '.'
    char map[MAP_HEIGHT][MAP_WIDTH];
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            map[row][col] = '.';
        }
    }

    // 2) 统计存活数量，并把每只生物画到地图上它自己的坐标处
    int bigCount = 0;
    int smallCount = 0;
    for (auto c : creatures)
    {
        if (c->isAlive() == false)
        {
            continue;
        }

        // symbol() 是各子类自己给的代号：大鱼 'B'，小鱼 's'
        map[c->getY()][c->getX()] = c->symbol();

        // 按代号分类计数
        if (c->symbol() == 'B')
        {
            bigCount++;
        }
        else if (c->symbol() == 's')
        {
            smallCount++;
        }
    }

    // 3) 打印这一天的地图和存活统计
    cout << "===== 第 " << day << " 天结束 =====" << endl;
    for (int row = 0; row < MAP_HEIGHT; row++)
    {
        for (int col = 0; col < MAP_WIDTH; col++)
        {
            cout << map[row][col] << ' ';
        }
        cout << endl;
    }
    cout << "存活数量: 大鱼 " << bigCount << " 条, 小鱼 " << smallCount
         << " 条, 共 " << (bigCount + smallCount) << " 条" << endl;
    cout << endl;
}
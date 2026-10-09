//
// Created by 铲 on 2026/9/23.
//

#ifndef 生态系统模拟系统_WORLD_H
#define 生态系统模拟系统_WORLD_H
#include "Organism.h"
#include "bigFish.h"
#include "smallFish.h"
#include <vector>
#include <string>


class World{
private:
    std::vector<Organism*> creatures;    // 世界里所有的生物（存基类指针，才能同时装大鱼和小鱼）
    std::vector<std::string> dayEvents;  // 今天发生的事件，先攒起来，最后"有才汇报"
    int day;                             // 当前是第几天，从 1 开始
    int stepInDay;                       // 今天已经走了几步

    void removeDead();                   // 清理死掉的生物，并把它们占的内存释放掉
    void reportEvents();                 // 播报今天的事件（没有事件就什么都不打印）

public:
    // 每天固定走 3 步
    static const int STEPS_PER_DAY = 3;

    World();
    ~World();                            // 析构时释放所有生物，修复内存泄漏

    void step();                         // 推进"一步"
    void show();                         // 打印地图 + 存活数量（每天结束时用）
    void addCreature(Organism* c);       // 往世界里放一只生物
};


#endif //生态系统模拟系统_WORLD_H
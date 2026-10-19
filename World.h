//
// Created by 铲 on 2026/9/23.
//

#ifndef 生态系统模拟系统_WORLD_H
#define 生态系统模拟系统_WORLD_H
#include "Organism.h"
#include "bigFish.h"
#include "smallFish.h"
#include "wolf.h"
#include <vector>
#include <string>


class World{
private:
    std::vector<Organism*> creatures; // 世界里所有的生物（存基类指针，才能同时装大鱼和小鱼）
    std::vector<std::string> dayEvents;  // 今天发生的事件，先攒起来，最后"有才汇报"
    int day;                             // 当前是第几天，从 1 开始
    int stepInDay;                       // 今天已经走了几步

    // ============ 地形底图（这张地图的"正式档案"）============
    // 每个格子存一个字符：'.' 表示水，'#' 表示陆地。
    // 它必须是 World 的成员而不是某个函数里的局部变量，因为有两个地方要用它：
    //   show()    —— 每天结束时画地图
    //   canEnter()—— 生物每走一步前判定"这格我能不能进"
    // 做成成员，两边读的是同一份数据，不会各画各的导致判定和显示对不上。
    char terrain[MAP_HEIGHT][MAP_WIDTH];

    void removeDead();                   // 清理死掉的生物，并把它们占的内存释放掉
    void reportEvents();                 // 播报今天的事件（没有事件就什么都不打印）

public:
    // 每天固定走 3 步
    static const int STEPS_PER_DAY = 3;

    World();
    ~World();                            // 析构时释放所有生物，修复内存泄漏

    void step();                         // 推进"一步"
    void show();                         // 打印地图 + 存活数量（每天结束时用）
    void addCreature(Organism* c);   // 往世界里放一只生物

    // 判定坐标 (x, y) 这一格，生物能不能进去。
    // habitat 是生物自己的栖息地属性（鱼是 '.'，wolf 是 '#'）——
    // 只有这一格的地形和它一致，才允许踏入。
    // 返回 true = 能进，false = 越界或者地形不符（原地不动）。
    // 声明成 const：这个函数只读 terrain，不改 World 的任何状态。
    bool canEnter(int x, int y, char habitat) const;
};


#endif //生态系统模拟系统_WORLD_H
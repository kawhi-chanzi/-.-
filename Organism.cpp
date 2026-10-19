//
// Created by 铲 on 2026/9/21.
//

#include "Organism.h"

#include "World.h"      // update 里要调 world->canEnter(...)，必须看到 World 的完整定义
#include <cstdlib>      // rand() 需要它

Organism::Organism(int life, int x, int y, int speed, int energy)
: alive(true), age(0), age_max(life), x(x), y(y), speed(speed), energy(energy) {}

void Organism::update(World* world)
{
    // 1) 先处理年龄：age 每步 +1，到达 age_max 就自然死亡
    age++;
    if (age >= age_max)
    {
        alive = false;
        return;   // 已经老死，就不用再耗能量、也不用再移动了
    }

    // 2) 每走一步消耗 1 点能量（不管这一步实际走了几格）
    energy--;

    // 能量耗尽就饿死。
    // 说明：这里修正了原来的写法——原来 energy<=0 时执行的是 age--，
    // 相当于让生物"返老还童"，年龄永远到不了 age_max，就成了永生的，
    // 生态链也就不会有新陈代谢了。改成饿死才符合"能量"这两个字的含义。
    if (energy <= 0)
    {
        alive = false;
        return;
    }

    // 3) 随机挑一个方向：dx、dy 各自在 -1 ~ 1 之间取值，
    //    但不允许两个同时为 0（那样就等于原地没动，白走一步）。
    int dx;
    int dy;
    do
    {
        dx = rand() % 3 - 1;   // rand()%3 得到 0/1/2，再减 1 就是 -1/0/1
        dy = rand() % 3 - 1;
    } while (dx == 0 && dy == 0);

    // 4) 随机决定这一步走几格：1 ~ speed 格。
    //    speed 越大平均走得越远。大鱼 speed=2、小鱼 speed=1，
    //    所以大鱼整体游得更快，也就更容易追上小鱼。
    int stepCount = rand() % speed + 1;

    // 5) 先算出"想去哪"。注意这里不再对地图取模绕回——环形地图已经取消，
    //    越界不再靠"从对面绕回来"解决，而是交给下面的 canEnter 判定。
    int nx = x + dx * stepCount;
    int ny = y + dy * stepCount;

    // 6) 先判再动：只有目标格的地形和本生物 habitat() 一致，才真正落位。
    //    越界、或者地形不符（比如鱼想游上陆地、狼想下水），就原地不动，
    //    但能量在上一步已经扣掉了——"走不动的这一步照样要消耗体力"。
    if (world != nullptr && world->canEnter(nx, ny, habitat()) == true)
    {
        x = nx;
        y = ny;
    }
}

bool Organism::isAlive()
{
    return alive;
}

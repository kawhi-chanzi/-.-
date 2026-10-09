//
// Created by 铲 on 2026/9/21.
//

#include "Fish.h"

#include <cstdlib>   // rand() 需要它

Fish::Fish(int life,int x, int y, int speed,int energy):
Organism(life),x(x),y(y),speed(speed),energy(energy){}

int Fish::getX() const
{
    return x;
}

int Fish::getY() const
{
    return y;
}

void Fish::update()
{
    // 1) 先交给父类处理"年龄"：age 每步 +1，到达 age_max 就自然死亡
    Organism::update();

    // 已经老死了，就不用再游、也不用再消耗能量了，直接返回
    if (alive == false)
    {
        return;
    }

    // 2) 每走一步消耗 1 点能量
    energy--;

    // 能量耗尽就饿死。
    // 说明：这里修正了原来的写法——原来 energy<=0 时执行的是 age--，
    // 相当于让鱼"返老还童"，年龄永远到不了 age_max，鱼就成了永生的，
    // 生态链也就不会有新陈代谢了。改成饿死才符合"能量"这两个字的含义。
    if (energy <= 0)
    {
        alive = false;
        return;
    }

    // 3) 随机游动：方向和步数都随机
    //
    // 3.1 随机挑一个方向。dx、dy 各自在 -1 ~ 1 之间取值，
    //     但不允许两个同时为 0（那样就等于原地没动，白走一步）。
    int dx;
    int dy;
    do
    {
        dx = rand() % 3 - 1;   // rand()%3 得到 0/1/2，再减 1 就是 -1/0/1
        dy = rand() % 3 - 1;
    } while (dx == 0 && dy == 0);

    // 3.2 随机决定这一步走几格：1 ~ speed 格。
    //     speed 越大平均走得越远。大鱼 speed=2、小鱼 speed=1，
    //     所以大鱼整体游得更快，也就更容易追上小鱼。
    int stepCount = rand() % speed + 1;

    // 3.3 更新坐标，并用取模实现"环形地图"：
    //     游出右边就从左边出来，游出上边就从下边出来。
    //     先加 MAP_WIDTH 再取模，是为了处理负数——
    //     C++ 里负数取模结果仍然是负数（比如 -3 % 20 == -3），加上一整圈就正过来了。
    x = ((x + dx * stepCount) % MAP_WIDTH + MAP_WIDTH) % MAP_WIDTH;
    y = ((y + dy * stepCount) % MAP_HEIGHT + MAP_HEIGHT) % MAP_HEIGHT;
}
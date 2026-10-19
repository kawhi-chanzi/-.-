//
// Created by 铲 on 2026/9/21.
//

#ifndef 生态系统模拟系统_ORGANISM_H
#define 生态系统模拟系统_ORGANISM_H

#include <string>

// ============ 前置声明 ============
// update() 需要一个 World* 参数，但 World.h 里又会 #include Organism.h
// （World 需要存 Organism*），两个头文件互相包含就成了死循环。
// 这里其实只需要告诉编译器"有这么个叫 World 的类"，
// 所以先用前置声明顶着，真正的 #include "World.h" 写在 Organism.cpp 里。
class World;

class Organism
{
protected:
    bool alive;
    int age;
    int age_max;

    // ============ 位置与移动能力（从 Fish 上提到基类）============
    // 原来这几个成员只写在 Fish 里，wolf 又照抄了一份，两边各写一遍很容易漏改。
    // 上提到基类之后，"生物会在图上移动"这件事就只有一份定义，
    // 移动逻辑也就能整段写进基类的 update()，子类不用再重抄一遍。
    int x;        // 地图横坐标（列）
    int y;        // 地图纵坐标（行）
    int speed;    // 速度：一步最多走几格，实际步数是随机的 1 ~ speed
    int energy;   // 剩余能量：每走一步 -1，减到 0 就饿死
public:
    // life = 寿命上限；x、y = 初始坐标；speed = 速度；energy = 初始能量
    Organism(int life, int x, int y, int speed, int energy);

    // 推进"一步"：年龄 +1、耗 1 点能量、随机移动一格（先判地形再落位）。
    // world 是当前世界——update 里要靠它调 world->canEnter() 判断目标格能不能进；
    // 传 nullptr 表示跳过地形判定（留给"子类自己想控制移动"的情况）。
    virtual void update(World* world);
    bool isAlive();
    virtual ~Organism()=default;

    // ============ 以下接口是为了支持"大鱼吃小鱼"和地图显示新增的 ============
    // 全部放在基类里，并且每一个都给了默认实现。
    // 这样做的好处：子类只需要覆写自己关心的那几个方法，
    // 以后再加别的生物（比如水草）时，不用把所有方法都重写一遍。

    // 生物在地图上的横坐标。坐标已经上提到基类，这里直接返回 x，
    // 子类不用再各自覆写一遍。
    virtual int getX() const { return x; }

    // 生物在地图上的纵坐标，含义同上
    virtual int getY() const { return y; }

    // 这个生物被吃掉时能提供多少能量。
    // 返回 0 表示"不能吃"。大鱼就是靠这个判断对方是不是猎物的：
    // 大鱼自己不覆写、用默认值 0，所以不会出现大鱼吃大鱼的情况。
    virtual int foodValue() const { return 0; }

    // 尝试吃掉另一个生物，吃到返回 true，够不着或者不能吃返回 false。
    // 基类默认谁都不吃，只有 bigFish 会覆写它。
    virtual bool tryEat(Organism* other) { return false; }

    // 立刻结束生命（被吃掉时由捕食者调用）。
    // alive 是 protected 的，外界直接改不了，所以必须留这么一个"口子"。
    virtual void kill() { alive = false; }

    // 播报事件时显示的名字，例如 "大鱼"、"小鱼"
    virtual std::string name() const { return "生物"; }

    // 画地图时用哪个字符代表自己，例如 'B'、's'
    virtual char symbol() const { return '?'; }

    // 栖息地：基类默认生物住在水里（'.'）。
    // update() 走到"判定这一步"时，会把它和自己的目标格地形比对：
    // 地形和栖息地一致才允许踏入。wolf 覆写成 '#' 就表示住在陆地。
    virtual char habitat() const { return '.'; }
};


#endif //生态系统模拟系统_ORGANISM_H

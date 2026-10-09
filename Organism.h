//
// Created by 铲 on 2026/9/21.
//

#ifndef 生态系统模拟系统_ORGANISM_H
#define 生态系统模拟系统_ORGANISM_H

#include <string>

class Organism
{
protected:
    bool alive;
    int age;
    int age_max;
public:
    Organism(int life);
    virtual void update();
    bool isAlive();
    virtual ~Organism()=default;

    // ============ 以下接口是为了支持"大鱼吃小鱼"和地图显示新增的 ============
    // 全部放在基类里，并且每一个都给了默认实现。
    // 这样做的好处：子类只需要覆写自己关心的那几个方法，
    // 以后再加别的生物（比如水草）时，不用把所有方法都重写一遍。

    // 生物在地图上的横坐标。只有 Fish 及其子类有真实坐标，其他生物默认返回 0
    virtual int getX() const { return 0; }

    // 生物在地图上的纵坐标，含义同上
    virtual int getY() const { return 0; }

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
};


#endif //生态系统模拟系统_ORGANISM_H

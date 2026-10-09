//
// Created by 铲 on 2026/9/21.
//

#ifndef 生态系统模拟系统_FISH_H
#define 生态系统模拟系统_FISH_H
#include "Organism.h"

// ============ 地图尺寸 ============
// 整个水域是 MAP_WIDTH 列 × MAP_HEIGHT 行的网格（也就是 20 × 10）。
// 鱼游出边界后会从对面绕回来（环形地图），所以 Fish 和 World 都要用这两个常量。
// 统一放在这里定义，避免两边各写一份、以后改的时候漏掉一个导致对不上。
const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 10;

class Fish:public Organism
{
    protected:
    int x;
    int y;
    int speed;
    int energy;
    public:
    Fish(int life,int x,int y,int speed,int energy);
    virtual void update() override;

    // ============ 给 World 用的坐标读取接口 ============
    // x、y 是 protected 的，而 World 手里拿的是 Organism* 基类指针，读不到子类的成员，
    // 所以必须提供这两个 public 方法（捕食判定和画地图都要读坐标）。
    int getX() const override;
    int getY() const override;
};




#endif //生态系统模拟系统_FISH_H
//
// Created by 铲 on 2026/9/21.
//

#ifndef 生态系统模拟系统_FISH_H
#define 生态系统模拟系统_FISH_H
#include "Organism.h"

// ============ 地图尺寸 ============
// 整个地图是 MAP_WIDTH 列 × MAP_HEIGHT 行的网格（也就是 20 × 10）。
// 放在这里定义，World 的地形数组 terrain 和 canEnter 都要用它。
// 注意：环形地图已经取消——游到边界外不再从对面绕回来，
//       越界统一由 World::canEnter 判掉（进不去就原地不动）。
const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 10;

class Fish:public Organism
{
public:
    Fish(int life,int x,int y,int speed,int energy);

    // 鱼没有额外的行为，走基类的"耗能量 + 地形判定移动"即可
    virtual void update(World* world) override;

    // 注意：这里不再声明 getX/getY。
    // 坐标 x、y 和这两个读取接口都已经上提到 Organism，
    // 子类再覆写一遍就是重复劳动，删掉。
};


#endif //生态系统模拟系统_FISH_H

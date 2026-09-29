//
// Created by 铲 on 2026/9/21.
//

#ifndef 生态系统模拟系统_FISH_H
#define 生态系统模拟系统_FISH_H
#include "Organism.h"

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
};






#endif //生态系统模拟系统_FISH_H

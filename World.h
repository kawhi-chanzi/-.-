//
// Created by 铲 on 2026/9/23.
//

#ifndef 生态系统模拟系统_WORLD_H
#define 生态系统模拟系统_WORLD_H
#include "Organism.h"
#include "bigFish.h"
#include "smallFish.h"
#include <vector>


class World{
private:
    std::vector<Organism*> creatures;
public:
    void step();
    void show();
    void addCreature(Organism* c);

};


#endif //生态系统模拟系统_WORLD_H

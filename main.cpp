//
// Created by ²ù on 2026/9/21.
//
#include <iostream>

#include "World.h"

using namespace std;

int main() {
    World world;
    world.addCreature(new smallFish(1,1));
    world.addCreature(new bigFish(2,2));
    for (int i=0;i<10;i++)
    {
        world.step();
        world.show();
    }
    return 0;
}
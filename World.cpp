//
// Created by 铲 on 2026/9/23.
//

#include "World.h"

#include <iostream>

#include "Organism.h"
using namespace std;
void World::addCreature(Organism* c)
{
    creatures.push_back(c);
}
void World::step()
{
    for (auto c : creatures)
    {
        if (c->isAlive()==true)
        {
            c->update();
        }
    }
}

void World::show()
{
    int cnt=0;
    for (auto c : creatures)
    {
        if (c->isAlive()==true)
        {
            cnt++;
        }
    }
    cout<<"存活的数量: "<<cnt<<endl;
}

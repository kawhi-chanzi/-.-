//
// Created by 铲 on 2026/9/21.
//

#include "Organism.h"
Organism:: Organism(int life)
:alive(true),age(0),age_max(life){}

 void Organism::update()
{
    age++;
    if (age>=age_max)
    {
        alive = false;
    }
}

    bool Organism::isAlive()
{
    return alive;
}
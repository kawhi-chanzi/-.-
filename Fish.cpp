//
// Created by 铲 on 2026/9/21.
//

#include "Fish.h"
Fish::Fish(int life,int x, int y, int speed,int energy):
Organism(life),x(x),y(y),speed(speed),energy(energy){}
void Fish::update()
{
    Organism::update();

    energy--;
    if(energy<=0)
    {
        age--;
    }
    x+=speed;
}
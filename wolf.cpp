//
// Created by 铲 on 2026/10/14.
//

#include "wolf.h"

#include <cstdlib>     // rand() 需要它
#include "Fish.h"      // MAP_WIDTH / MAP_HEIGHT 这两个地图常量定义在这里
wolf::wolf(int life,int x, int y,int speed,int energy) :
Organism(life),x(x),y(y),speed(speed),energy(energy){}
int wolf::getX() const
{
    return x;
}
int wolf::getY() const
{
    return y;
}
void wolf::update()
{
    Organism::update();
    if (alive==false)
    {return ;}
    energy--;
    if (energy<=0)
    {
        alive=false;
        return;
    }
    int dx;
    int dy;
    do
    {
        dx=rand()%3-1;
        dy=rand()%3-1;
    }
    while (dx==0&&dy==0);
    int stepCount=rand()%speed+1;
    x = ((x + dx * stepCount) % MAP_WIDTH + MAP_WIDTH) % MAP_WIDTH;
    y = ((y + dy * stepCount) % MAP_HEIGHT + MAP_HEIGHT) % MAP_HEIGHT;
}
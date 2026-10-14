//
// Created by 铲 on 2026/10/14.
//

#ifndef 类图_PUML_WOLF_H
#define 类图_PUML_WOLF_H
#include "Organism.h"

class wolf: public Organism
{
protected:
    int x;
    int y;
    int speed;
    int energy;
public:
    wolf(int life,int x, int y,int speed, int energy);
    virtual void update() override;
    int getX() const override;
    int getY() const override;
};


#endif //类图_PUML_WOLF_H

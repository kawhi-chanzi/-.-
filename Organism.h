//
// Created by 铲 on 2026/9/21.
//

#ifndef 生态系统模拟系统_ORGANISM_H
#define 生态系统模拟系统_ORGANISM_H


class Organism
{
protected:
    bool alive;
    int age;
    int age_max;
public:
    Organism(int life);
    virtual void update();
    bool isAlive();
    virtual ~Organism()=default;
};


#endif //生态系统模拟系统_ORGANISM_H

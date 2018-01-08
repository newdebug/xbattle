#ifndef MONSTER_H
#define MONSTER_H

#include "Actor.h"

class Monster : public Actor
{
public:
    ~Monster();

    static Monster *create(ActorBreed *breed);
    virtual void update(float delta);
    virtual void startActions(float delta);
    virtual void endLife();
    virtual bool isLifeless();

private:
    Monster(ActorBreed *breed);
    bool m_isDead;
};

#endif // MONSTER_H

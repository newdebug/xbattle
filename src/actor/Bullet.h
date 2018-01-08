#ifndef BULLET_H
#define BULLET_H

#include "Actor.h"

class Bullet : public Actor
{
public:
    static Bullet *create(ActorBreed *breed);
    virtual void update(float delta);
    virtual void startActions(float delta);

private:
    Bullet(ActorBreed *breed);
};

#endif // BULLET_H

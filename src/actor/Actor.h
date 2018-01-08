/**
 * @date 2017
 * @filename Actor.h
 * @class Actor
 * @author Yuri Young<yuri.young@qq.com>
 * @qq 12319597
 * Copyright (c) 2017 Yuri Young, All rights reserved.
 * @description Project created by QtCreator.
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <cocos2d.h>

#include "ActorBreed.h"

class Actor : public cocos2d::Sprite
{
public:
    Actor(ActorBreed *breed);
    virtual ~Actor();

    virtual bool initialize();
    virtual void update(float delta) = 0;
    virtual void startActions(float delta) = 0;
    virtual void endLife();
    virtual bool isLifeless();

    virtual cocos2d::Vector<Actor *> &bullets();

    ActorBreed *breed();
    void setBreed(ActorBreed *breed);

protected:
    virtual void installEvents();

private:
    ActorBreed* m_breed;
    cocos2d::Vector<Actor*> m_bullets;
};

#endif // ACTOR_H

/**
 * @description Project created by QtCreator.
 * @date 2017-11-29
 * @filename Actor3D.h
 * @class Actor3D
 * @author Yuri Young<yuri.young@qq.com>
 * @qq 12319597
 * Copyright (c) 2017 Yuri Young, All rights reserved.
 */
#ifndef ACTOR3D_H
#define ACTOR3D_H

#include <cocos2d.h>

class ActorBreed;

class Actor3D : public cocos2d::Sprite3D
{
public:
    Actor3D(ActorBreed *breed);
    virtual ~Actor3D();

    static Actor3D *create(ActorBreed *breed);
    virtual bool initialize();

    ActorBreed *breed();
    void setBreed(ActorBreed *breed);

    virtual void startActions(float delta);
    virtual void endLife();
    virtual bool isLifeless();

protected:
    virtual void installEvents();

private:
    ActorBreed* m_breed;
    bool m_isDead;
};

#endif // ACTOR3D_H

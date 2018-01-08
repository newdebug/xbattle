/**
 * @description Project created by QtCreator.
 * @date 2017-11-29
 * @filename Actor3D.cpp
 * @class Actor3D
 * @author Yuri Young<yuri.young@qq.com>
 * @qq 12319597
 * Copyright (c) 2017 Yuri Young, All rights reserved.
 */
#include <SimpleAudioEngine.h>

#include "Actor3D.h"
#include "ActorBreed.h"

USING_NS_CC;
using namespace CocosDenshion;

Actor3D::Actor3D(ActorBreed *breed)
    : m_breed(breed),
      m_isDead(false)
{
    m_breed->retain();
}

Actor3D::~Actor3D()
{
    m_breed->release();
}

Actor3D *Actor3D::create(ActorBreed *breed)
{
    Actor3D *actor3D = new (std::nothrow)Actor3D(breed);
    if (actor3D->initialize())
    {
        return actor3D;
    }

    CC_SAFE_DELETE(actor3D);

    return nullptr;
}

bool Actor3D::initialize()
{
    CC_ASSERT(m_breed != nullptr);
    CCASSERT(m_breed->filename().length() >= 4, "invalid filename for Sprite3D");

    if(Sprite3D::init() && this->initWithFile(m_breed->filename()) )
    {
        this->_contentSize = this->getBoundingBox().size;
        this->autorelease();
        this->installEvents();
        this->scheduleUpdate();
        return true;
    }

    return false;
}

ActorBreed *Actor3D::breed()
{
    return m_breed;
}

void Actor3D::setBreed(ActorBreed *breed)
{
    if( breed == nullptr || m_breed == breed )
        return;

    // 释放之前的breed引用次数
    if( m_breed )
        m_breed->release();

    // 指向新的breed,同时新的breed引用次数增加
    m_breed = breed;
    m_breed->retain();
}

void Actor3D::startActions(float delta)
{
    this->setVisible(true);
    m_isDead = false;

    // 设置随机位置
    Size size = this->getContentSize();
    float minX = size.width / 2;
    float maxX = Director::getInstance()->getWinSize().width - size.height / 2;
    float actualHorizontal = CCRANDOM_0_1() * (maxX - minX) + minX;
    this->setPosition(actualHorizontal, maxX);

    // 设置随机旋转
    float minDuration = 3.0f;
    float maxDuration = 12.0f;
    float rangeDuration = maxDuration - minDuration;
    float actualDuration = CCRANDOM_0_1() * (rangeDuration) + minDuration;

    float actualRotate = CCRANDOM_0_1() * (actualDuration * 0.01f) + 1.0f;
    float actualAngle = CCRANDOM_MINUS1_1() * 360;

    auto *move = MoveTo::create(actualDuration, Point(this->getPosition().x, -size.height / 2));
    CallFunc *moveDone = CallFunc::create([=](){
        this->setVisible(false);
        this->stopAllActions();
        this->startActions(delta);
    });

    this->runAction(RepeatForever::create(RotateBy::create(actualRotate, Vec3(actualAngle, 0.f, actualAngle))));
    this->runAction(Sequence::create(move, moveDone, nullptr));
}

void Actor3D::endLife()
{
    m_isDead = true;
    this->stopAllActions();
    this->setVisible(false);
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    SimpleAudioEngine::getInstance()->playEffect("audio/sounds/explode_0.wav");

    this->scheduleOnce(schedule_selector(Actor3D::startActions), 0.4f);
}

bool Actor3D::isLifeless()
{
    return m_isDead;
}

void Actor3D::installEvents()
{

}

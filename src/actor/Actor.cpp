#include "Actor.h"

USING_NS_CC;

Actor::Actor(ActorBreed *breed)
    : m_breed(breed)
{
    m_breed->retain();
}

Actor::~Actor()
{
    m_breed->release();
}

bool Actor::initialize()
{
    CC_ASSERT(m_breed != nullptr);

    if( this->initWithFile(m_breed->filename()) )
    {
        this->autorelease();
        this->installEvents();
        this->scheduleUpdate();
        return true;
    }
    else if( !m_breed->frames().empty() && initWithSpriteFrame(m_breed->frames().front()) )
    {
        this->autorelease();
        this->installEvents();
        this->scheduleUpdate();
        auto animation = Animation::createWithSpriteFrames(m_breed->frames(), 1.0f / 30);
        this->runAction(RepeatForever::create(Animate::create(animation)));
        return true;
    }
    else // 使用默认的纹理初始化
    {
        // 默认初始化一张白色纹理给角色精灵
        RenderTexture *rt = RenderTexture::create(64, 64);
        rt->beginWithClear(1.0, 1.0, 1.0, 1.0);
        rt->end();
        this->initWithTexture(rt->getSprite()->getTexture());
        this->autorelease();
        this->installEvents();
        this->scheduleUpdate();
        return true;
    }

    return false;
}

void Actor::endLife()
{
    // Do nothing
}

bool Actor::isLifeless()
{
    return true;
}

ActorBreed *Actor::breed()
{
    return m_breed;
}

void Actor::setBreed(ActorBreed *breed)
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

cocos2d::Vector<Actor *> &Actor::bullets()
{
    m_bullets.reserve(0);
    return m_bullets;
}

void Actor::installEvents()
{
    // Nothing to do
}


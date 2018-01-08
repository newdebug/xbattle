#include <SimpleAudioEngine.h>

#include "Monster.h"
#include "BrokenBangAction.h"

USING_NS_CC;
using namespace CocosDenshion;

Monster::Monster(ActorBreed *breed)
    : Actor(breed),
      m_isDead(false)
{
    cocos2d::log("[Monster] ref count retain: %d", this->breed()->getReferenceCount());
}

Monster::~Monster()
{
    cocos2d::log("[Monster] ref count release: %d", this->breed()->getReferenceCount());
}

Monster *Monster::create(ActorBreed *breed)
{
    Monster *monster = new Monster(breed);
    if (monster->initialize())
    {
        return monster;
    }

    CC_SAFE_DELETE(monster);

    return nullptr;
}

void Monster::startActions(float delta)
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

    this->runAction(RepeatForever::create(RotateBy::create(actualRotate, actualAngle)));
    this->runAction(Sequence::create(move, moveDone, nullptr));
}

void Monster::endLife()
{
    m_isDead = true;
    this->stopAllActions();
    this->setVisible(false);
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    SimpleAudioEngine::getInstance()->playEffect("audio/sounds/explode_0.wav");

    this->scheduleOnce(schedule_selector(Monster::startActions), 0.4f);
}

bool Monster::isLifeless()
{
    return m_isDead;
}

void Monster::update(float delta)
{
    CC_UNUSED_PARAM(delta);
}



#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet(ActorBreed *breed)
    : Actor(breed)
{

}

Bullet *Bullet::create(ActorBreed *breed)
{
    Bullet *bullet = new Bullet(breed);
    if (bullet->initialize())
    {
        return bullet;
    }

    CC_SAFE_DELETE(bullet);

    return nullptr;
}

void Bullet::update(float delta)
{
    CC_UNUSED_PARAM(delta);
}

void Bullet::startActions(float delta)
{
    Size size = Director::getInstance()->getWinSize();
    auto moveby = MoveBy::create(delta, Vec2(0, size.height * 0.7f));
    CallFunc *moveDone = CallFunc::create([=](){
        this->setVisible(false);
        this->stopAllActions();
    });
    this->runAction(Sequence::create(moveby, moveDone, nullptr));
}

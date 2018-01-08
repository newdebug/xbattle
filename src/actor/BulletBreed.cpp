#include "BulletBreed.h"
#include "Bullet.h"

USING_NS_CC;

BulletBreed::BulletBreed()
{

}

bool BulletBreed::init()
{
    const std::string filename = "images/bullet.png";
    if( !FileUtils::getInstance()->isFileExist(filename) )
    {
#if COCOS2D_DEBUG
    char msg[256] = { 0 };
    sprintf(msg, "[BulletBreed] Invalid sprite filename: %s", filename);
    CCASSERT(FileUtils::getInstance()->isFileExist(filename), msg);
#endif
        return false;
    }
    this->setFilename(filename);

    return true;
}

Actor *BulletBreed::createActor()
{
    if( this->init() )
    {
        Bullet *bullet = Bullet::create(this);
        if( bullet )
        {
            bullet->setVisible(false);
            return bullet;
        }
    }

    return nullptr;
}

Actor *BulletBreed::createBullet()
{
    // breed由Actor内部增加/递减引用次数并释放内存
    BulletBreed *breed = new BulletBreed;
    breed->autorelease();
    return breed->createActor();
}

cocos2d::Vector<Actor *> BulletBreed::createBullets(int count)
{
    // breed由Actor内部增加/递减引用次数并释放内存
    BulletBreed *breed = new BulletBreed;
    breed->autorelease();
    Vector<Actor *> bullets(count);
    for(int i = 0; i < count; ++i)
    {
        bullets.pushBack(breed->createActor());
    }
    return bullets;
}

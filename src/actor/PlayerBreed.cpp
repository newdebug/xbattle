#include "PlayerBreed.h"
#include "Player.h"

USING_NS_CC;

PlayerBreed::PlayerBreed()
{

}

PlayerBreed::~PlayerBreed()
{

}

bool PlayerBreed::init()
{
    std::string frameList("images/drone_yellow.plist");
    if( !FileUtils::getInstance()->isFileExist(frameList) )
    {
#if COCOS2D_DEBUG > 0
    char msg[256] = { 0 };
    sprintf(msg, "[Actor] Invalid sprite filename: %s", frameList);
    CCASSERT(FileUtils::getInstance()->isFileExist(frameList), msg);
#endif
        return false;
    }
    auto spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile(frameList);
    cocos2d::Vector<SpriteFrame*> frames;
    std::string str;
    for (int i = 0; i < 4; ++i)
    {
        str.append("drone_yellow_");
        str.append(std::to_string(i));
        str.append(".png");
        SpriteFrame *frame = spriteFrameCache->getSpriteFrameByName(str);
        frames.pushBack(frame);
        str.clear();
    }
    this->setFrames(frames);
    return true;
}

Actor *PlayerBreed::createActor()
{
    if( this->init() )
    {
        Player *player = Player::create(this);
        if( player )
        {
            return player;
        }
    }

    return nullptr;
}

// static member function
Actor *PlayerBreed::createPlayer()
{
    // breed由Actor内部增加/递减引用次数并释放内存
    PlayerBreed *breed = new PlayerBreed;
    breed->autorelease();
    return breed->createActor();
}

int PlayerBreed::role() const
{
    // always returns hero role.
    return ActorBreed::HeroRole;
}

#include "ActorBreed.h"
//#include "Actor.h"

USING_NS_CC;

ActorBreed::ActorBreed()
    : m_role(ActorBreed::UnknowRole)
{

}

ActorBreed::~ActorBreed()
{
    m_frames.clear();
    cocos2d::log("[ActorBreed] ref count release: %d", this->getReferenceCount());
}

/*
Actor *ActorBreed::createActor()
{
    // breed由Actor内部增加/递减引用次数并释放内存
    //ActorBreed *breed = new ActorBreed;
    if( this->init() )
    {
        Actor *actor = Actor::create(this);
        return actor;
    }

    //CC_SAFE_DELETE(breed);
    return nullptr;
}

cocos2d::Vector<Actor *> ActorBreed::createActors(int count)
{
    cocos2d::Vector<Actor *> actors;

    // breed由Actor内部增加/递减引用次数并释放内存
    //ActorBreed *breed = new ActorBreed;
    if( this->init() )
    {
        for(int i = 0; i < count; ++i)
        {
            Actor *actor = Actor::create(this);
            actors.pushBack(actor);
        }
        return actors;
    }

    //CC_SAFE_DELETE(breed);
    return cocos2d::Vector<Actor *>();
}
*/

int ActorBreed::role() const
{
    return m_role;
}

void ActorBreed::setRole(const ActorBreed::BreedRoles &role)
{
    m_role = role;
}

int ActorBreed::health() const
{
    return m_health;
}

void ActorBreed::setHealth(int health)
{
    m_health = health;
}

std::string ActorBreed::filename() const
{
    return m_filename;
}

void ActorBreed::setFilename(const std::string &filename)
{
    m_filename = filename;
}

cocos2d::Vector<cocos2d::SpriteFrame *> ActorBreed::frames() const
{
    return m_frames;
}

void ActorBreed::setFrames(const cocos2d::Vector<cocos2d::SpriteFrame *> &frames)
{
    m_frames.clear();
    m_frames = frames;
    //cocos2d::Vector::swap(m_frames, frames);
}

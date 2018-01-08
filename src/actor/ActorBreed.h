#ifndef ACTORBREED_H
#define ACTORBREED_H

#include <cocos2d.h>

class Actor;

/**
 * @brief The ActorBreed class
 */
class ActorBreed : public cocos2d::Ref
{
public:
    enum BreedRoles
    {
        UnknowRole = 0,
        HeroRole = 1,
        MonsterRole = 2,
        SceneRole = 3
    };

    virtual ~ActorBreed();


    // 返回/设置角色种类
    virtual int role() const;
    virtual void setRole(const ActorBreed::BreedRoles &role);

    // 返回/设置血量
    virtual int health() const;
    virtual void setHealth(int health);

    // 返回/设置精灵文件
    virtual std::string filename() const;
    virtual void setFilename(const std::string &filename);

    // 返回/设置角色精灵帧
    virtual cocos2d::Vector<cocos2d::SpriteFrame *> frames() const;
    virtual void setFrames(const cocos2d::Vector<cocos2d::SpriteFrame*> &frames);

protected:
    ActorBreed();

    // 需要子类实现初始化
    virtual bool init() = 0;

    // 创建角色精灵
    virtual Actor *createActor() = 0;

private:
    ActorBreed::BreedRoles m_role;
    int m_health;
    std::string m_filename;
    cocos2d::Vector<cocos2d::SpriteFrame*> m_frames;
};

#endif // ACTORBREED_H

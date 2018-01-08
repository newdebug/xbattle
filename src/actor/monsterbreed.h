#ifndef MONSTERBREED_H
#define MONSTERBREED_H

#include "ActorBreed.h"

class Actor3D;

class MonsterBreed : public ActorBreed
{
public:
    ~MonsterBreed();

    static Actor3D *createMonster();
    static cocos2d::Vector<Actor3D *> createMonsters(int count);
    void addShader(Actor3D *sprite3d, const std::string &shaderKey);

    virtual int role() const;

protected:
    virtual bool init();
    virtual Actor *createActor();
    virtual Actor3D *createActor3D();

private:
    MonsterBreed();

private:
    cocos2d::GLProgramCache* m_shaderCache;
};

#endif // MONSTERBREED_H

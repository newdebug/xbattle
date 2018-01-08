#ifndef MISSIONLAYER_H
#define MISSIONLAYER_H

#include <cocos2d.h>

class Actor;
class Actor3D;
class PlayerBreed;
class MonsterBreed;
class GameScene;

class MissionLayer : public cocos2d::Layer
{
public:
    MissionLayer();
    ~MissionLayer();

    void setGameScene(GameScene *scene);

    virtual bool init() override;
    void update(float delta);

    CREATE_FUNC(MissionLayer)

private:
    void createMonsters();

private:
    GameScene*      m_scene;
    cocos2d::ParticleSystemQuad*    m_particleBomb;
    cocos2d::Size   m_winSize;
    Actor*          m_hero;
    cocos2d::Vector<Actor3D*> m_monsters;

};

#endif // MISSIONLAYER_H

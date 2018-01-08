#include "MissionLayer.h"
#include "Actor.h"
#include "Actor3D.h"
#include "PlayerBreed.h"
#include "MonsterBreed.h"
#include "GameScene.h"

USING_NS_CC;

MissionLayer::MissionLayer()
    : m_particleBomb(nullptr),
      m_scene(nullptr)
{

}

MissionLayer::~MissionLayer()
{
    this->removeAllChildren();
    m_monsters.clear();
}

void MissionLayer::setGameScene(GameScene *scene)
{
    m_scene = scene;
}

bool MissionLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    this->setCameraMask(2);

    this->scheduleUpdate();

    m_winSize = Director::getInstance()->getWinSize();

    m_particleBomb = ParticleSystemQuad::create("particles/bomb.plist");
    m_particleBomb->stop();
    this->addChild(m_particleBomb);

    // add hero sprite
    m_hero = PlayerBreed::createPlayer();
    m_hero->setPosition( m_winSize.width / 2, m_hero->getContentSize().height / 2);
    this->addChild(m_hero, 1);

    // add monster sprite
    createMonsters();

    return true;
}

void MissionLayer::createMonsters()
{
    const int count = 5;
    m_monsters = MonsterBreed::createMonsters(count);
    if( m_monsters.empty() )
        return;

    for(int i = 0; i < count; ++i)
    {
        Actor3D *monster = m_monsters.at(i);
        monster->setVisible(false);
        //monster->setScale(5.0f);
        //monster->setGlobalZOrder(100.0f);
        this->addChild(monster);
        monster->scheduleOnce(schedule_selector(Actor3D::startActions), i * 0.5f);
    }
}

void MissionLayer::update(float delta)
{
    for(Actor3D *monster : m_monsters)
    {
        if( monster->isLifeless() )
            continue;

        for(Actor *bullet : m_hero->bullets())
        {
            if( !bullet->isVisible() )
                continue;
            if (bullet->getBoundingBox().intersectsRect(monster->getBoundingBox()))
            {
                // TODO: 播放爆炸/死亡特效
                // TODO: 播放爆炸/死亡音效
                // TODO: 更新怪物命中后的属性
                // TODO: 英雄得分
                bullet->setVisible(false);
                monster->endLife();
                m_particleBomb->setPosition(monster->getPosition());
                m_particleBomb->start();
                m_scene->shakeScreen();

                // TODO: 如果怪物非一击毙命，需要实现怪物血量减少特效,则此处不使用break
                break;
            }
        } // end bullte for

        // 如果命中Hero
        if(m_hero->getBoundingBox().intersectsRect(monster->getBoundingBox()))
        {
            monster->setVisible(false);
            // TODO: 播放英雄死亡特效和音效
            // TODO: 如果非一击毙命，需实现英雄血量减少特效和属性更新
        }
    } // end monster for
}

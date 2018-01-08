#include <SimpleAudioEngine.h>

#include "Player.h"
#include "Bullet.h"
#include "BulletBreed.h"

USING_NS_CC;
using namespace CocosDenshion;

const int NUM_BULLET = 8;

Player::Player(ActorBreed *breed)
    : Actor(breed),
      m_actived(false),
      m_nextBulletIndex(0)
{
    m_bullets.reserve(NUM_BULLET);
}

Player::~Player()
{
    m_bullets.clear();
}

Player *Player::create(ActorBreed *breed)
{
    Player *player = new Player(breed);
    if ( player && player->initialize())
    {
        // 构建子弹
        player->m_bullets = BulletBreed::createBullets(NUM_BULLET);
        return player;
    }

    CC_SAFE_DELETE(player);

    return nullptr;
}

void Player::update(float delta)
{
    CC_UNUSED_PARAM(delta);
}

void Player::startActions(float delta)
{
    CC_UNUSED_PARAM(delta);
}

void Player::fire(float delta)
{
    CC_UNUSED_PARAM(delta);
    if( this->isActived() )
    {
        Actor *currentBullet = m_bullets.at(m_nextBulletIndex++);
        if( m_nextBulletIndex >= NUM_BULLET )
            m_nextBulletIndex = 0;

        Vec2 pos = this->getPosition();
        currentBullet->setPosition(pos.x, pos.y + this->getContentSize().height / 2);
        if(!currentBullet->getParent())
            this->getParent()->addChild(currentBullet);
        currentBullet->setVisible(true);
        currentBullet->startActions(0.5f);

        SimpleAudioEngine::getInstance()->playEffect("audio/sounds/laser_0.wav");
    }
}

void Player::installEvents()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
    m_listener->onTouchCancelled = CC_CALLBACK_2(Player::onTouchCancel, this);
    dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
}

void Player::setActived(bool actived)
{
    m_actived = actived;
    Action *scale = m_actived ? ScaleTo::create(0.2f, 1.1f) : ScaleTo::create(0.2f, 1.0f);
    this->runAction(scale);
}

bool Player::isActived()
{
    return m_actived;
}

cocos2d::Vector<Actor *> &Player::bullets()
{
    return m_bullets;
}

bool Player::onTouchBegan(Touch *touch, Event *e)
{
    CC_UNUSED_PARAM(e);

    if (this->getBoundingBox().containsPoint(touch->getLocation()))
    {
        this->setActived(true);
        // 吞没触摸事件,即不向下传递事件
        m_listener->setSwallowTouches(true);
        this->schedule(schedule_selector(Player::fire), 0.2f);
        return true;
    }

    m_listener->setSwallowTouches(false);
    return false;
}

void Player::onTouchMoved(Touch *touch, Event *e)
{
    CC_UNUSED_PARAM(e);

    if( this->isActived() )
    {
        Size winSize = Director::getInstance()->getWinSize();
        Size heroSize = this->getContentSize();

        Rect visibleView = Rect(heroSize.width / 2,
                                heroSize.height / 2,
                                winSize.width - heroSize.width / 2,
                                winSize.height - heroSize.height / 2);
        if (!visibleView.containsPoint(touch->getLocation()))
        {
            return;
        }

        Vec2 pos = this->getPosition() + touch->getDelta();
        auto move = MoveTo::create(0.06f, Point(pos.x, pos.y));
        this->runAction(move);
    }
}

void Player::onTouchEnded(Touch *touch, Event *e)
{
    CC_UNUSED_PARAM(e);
    this->setActived(false);
}

void Player::onTouchCancel(Touch *touch, Event *e)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(e);
    this->setActived(false);
}

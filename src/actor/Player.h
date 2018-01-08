#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"

class Player : public Actor
{
public:
    ~Player();

    static Player *create(ActorBreed *breed);

    virtual void update(float delta);
    virtual void startActions(float delta);
    virtual cocos2d::Vector<Actor *> &bullets();

    void fire(float delta);

    void setActived(bool actived = true);
    bool isActived();

protected:
    virtual void installEvents();
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *e);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *e);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *e);
    void onTouchCancel(cocos2d::Touch *touch, cocos2d::Event *e);

private:
    Player(ActorBreed *breed);

private:
    cocos2d::EventListenerTouchOneByOne* m_listener;
    cocos2d::Vector<Actor *> m_bullets;
    bool m_actived;
    int m_nextBulletIndex;
};

#endif // PLAYER_H

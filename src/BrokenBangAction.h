#ifndef BROKENBANGACTION_H
#define BROKENBANGACTION_H

#include <cocos2d.h>

class BrokenBangAction : public cocos2d::ActionInterval
{
public:
    BrokenBangAction();

    bool init(float duration, float speed, float accelerated);

    static BrokenBangAction *create(float duration, float speed);
    static BrokenBangAction *create(float duration, float speed, float accelerated);

    virtual BrokenBangAction *clone() const override;
    virtual BrokenBangAction *reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;

    virtual void update(float delta) override;

private:
    float m_speed;
    float m_accelerated;
    float m_lastUpdateTime;
};

#endif // BROKENBANGACTION_H

#include "BrokenBangAction.h"
#include "Actor.h"

USING_NS_CC;

BrokenBangAction::BrokenBangAction()
    : m_speed(0), m_accelerated(0.0f), m_lastUpdateTime(0.0f)
{

}

bool BrokenBangAction::init(float duration, float speed, float accelerated)
{
    if (!ActionInterval::initWithDuration(duration))
    {
        return false;
    }

    m_speed = speed;
    m_accelerated = accelerated;
    m_lastUpdateTime = 0.0f;

    return true;
}

BrokenBangAction *BrokenBangAction::create(float duration, float speed)
{
    return BrokenBangAction::create(duration, speed, 0.0f);
}

BrokenBangAction *BrokenBangAction::create(float duration, float speed, float accelerated)
{
    BrokenBangAction * brokenAction = new BrokenBangAction();
    if (brokenAction && brokenAction->init(duration, speed, accelerated))
    {
        brokenAction->autorelease();
        return brokenAction;
    }

    CC_SAFE_DELETE(brokenAction);
    return nullptr;
}

BrokenBangAction *BrokenBangAction::clone() const
{
    BrokenBangAction * brokenAction = new BrokenBangAction();
    brokenAction->init(_duration, m_speed, m_accelerated);
    return brokenAction;
}

BrokenBangAction *BrokenBangAction::reverse() const
{
    return BrokenBangAction::create(_duration, -m_speed, m_accelerated);
}

void BrokenBangAction::startWithTarget(Node *target)
{
    Actor *broken = dynamic_cast<Actor *>(target);
    CCASSERT(broken, "[BrokenBangAction] target must be Actor");

    ActionInterval::startWithTarget(target);
}

void BrokenBangAction::update(float delta)
{
    float dt = delta - m_lastUpdateTime;
    Actor * brokenActor = static_cast<Actor *>(_target);
    std::vector<V2F_C4B_T2F_Triangle> triangles = brokenActor->getSpritePolygonInfo();
    Size contentSize = brokenActor->getContentSize();

    float moveDistance = dt * m_speed;

    for (int i = 0; i < triangles.size(); ++i)
    {

        V2F_C4B_T2F_Triangle vct = triangles[i];
        Vec2 center = (vct.a.vertices + vct.b.vertices + vct.c.vertices) / 3;
        Vec2 v = center - Vec2(contentSize / 2);

        float d = v.distance(Vec2());
        float distX = 0;
        if (v.x != 0)
        {
            distX = v.x / d * moveDistance;
        }

        float distY = 0;
        if (v.y != 0 )
        {
            distY = v.y / d * moveDistance;
        }

        V2F_C4B_T2F *tri = (V2F_C4B_T2F *)&vct;
        for (int j = 0; j < 3; ++j)
        {
            tri[j].vertices.x += distX;
            tri[j].vertices.y += distY;
        }
    }

    brokenActor->setSpritePolygonInfo(triangles);

    m_speed += m_accelerated;
    m_lastUpdateTime = delta;
}

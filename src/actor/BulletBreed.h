#ifndef BULLETBREED_H
#define BULLETBREED_H

#include "ActorBreed.h"

class BulletBreed : public ActorBreed
{
public:
    static Actor *createBullet();
    static cocos2d::Vector<Actor *> createBullets(int count);

protected:
    virtual bool init();
    virtual Actor *createActor();

private:
    BulletBreed();
};

#endif // BULLETBREED_H

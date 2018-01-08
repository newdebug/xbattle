#ifndef PLAYERBREED_H
#define PLAYERBREED_H

#include "ActorBreed.h"

class PlayerBreed : public ActorBreed
{
public:
    ~PlayerBreed();

    static Actor *createPlayer();
    virtual int role() const;

protected:
    virtual bool init();
    // 创建角色精灵
    virtual Actor *createActor();

private:
    PlayerBreed();

private:

};

#endif // PLAYERBREED_H

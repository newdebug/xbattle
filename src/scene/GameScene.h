#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <cocos2d.h>

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    float noise(int x, int y);
    void shakeScreen();

    // a selector callback
    void menuCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene)
};

#endif // __GAME_SCENE_H__

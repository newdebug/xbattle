/**
 * @date 2017
 * @filename PreLoading.h
 * @class PreLoading
 * @author Yuri Young<yuri.young@qq.com>
 * @qq 12319597
 * Copyright (c) 2017 Yuri Young, All rights reserved.
 * @description Project created by QtCreator.
 */

#ifndef PRELOADSCENE_H
#define PRELOADSCENE_H

#include <cocos2d.h>

class PreLoadScene: public cocos2d::Scene
{
public:
    PreLoadScene();

    static cocos2d::Scene *createScene();

    virtual bool init();

    void loadMusic(const cocos2d::ValueVector &musicFiles);
    void loadEffect(const cocos2d::ValueVector &effectFiles);
    void loadSpriteSheets(const cocos2d::ValueVector &spriteSheets);
    void progressUpdate();

    virtual void onEnterTransitionDidFinish();

    CREATE_FUNC(PreLoadScene)

private:
    int m_sourceCount;
    float m_progressInterval;
    cocos2d::ProgressTimer* m_progress;
    cocos2d::Label* m_loadingLabel;
};

#endif // PRELOADSCENE_H

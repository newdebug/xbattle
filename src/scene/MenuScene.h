/**
 * @description Project created by QtCreator.
 * @date 2017-11-28
 * @filename MenuScene.h
 * @class MenuScene
 * @author Yuri Young<yuri.young@qq.com>
 * @qq 12319597
 * Copyright (c) 2017 Yuri Young, All rights reserved.
 */
#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <cocos2d.h>

class MenuScene : public cocos2d::Scene
{
public:

    enum MenuTag
    {
        StartTag = 1,
        SettingTag,
        ExitTag
    };

    static cocos2d::Scene *createScene();
    virtual bool init();

    void menuItemCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(MenuScene)
};

#endif // MENUSCENE_H

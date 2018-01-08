/**
 * @description Project created by QtCreator.
 * @date 2017-11-28
 * @filename MenuScene.cpp
 * @class MenuScene
 * @author Yuri Young<yuri.young@qq.com>
 * @qq 12319597
 * Copyright (c) 2017 Yuri Young, All rights reserved.
 */
#include "MenuScene.h"
#include "GameScene.h"
#include "PreLoadScene.h"

USING_NS_CC;

cocos2d::Scene *MenuScene::createScene()
{
    return MenuScene::create();;
}

bool MenuScene::init()
{
    if( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create color background
    auto colorLayer = LayerColor::create(Color4B(48, 0, 71, 255));
    this->addChild(colorLayer, -999);

    auto strings = FileUtils::getInstance()->getValueMapFromFile("lang/chinese_simple.plist");
    TTFConfig ttfConfig("fonts/PangYuTou.ttf", 32, GlyphCollection::DYNAMIC);

    // "开始""设置""退出"按钮
    Label *startLabel = Label::createWithTTF(ttfConfig, strings["start"].asString());
    Label *settingLabel = Label::createWithTTF(ttfConfig, strings["setting"].asString());
    Label *exitLabel = Label::createWithTTF(ttfConfig, strings["exit"].asString());

    auto startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MenuScene::menuItemCallback, this));
    startItem->setTag(MenuScene::StartTag);
    auto settingItem = MenuItemLabel::create(settingLabel, CC_CALLBACK_1(MenuScene::menuItemCallback, this));
    settingItem->setTag(MenuScene::SettingTag);
    auto extItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(MenuScene::menuItemCallback, this));
    extItem->setTag(MenuScene::ExitTag);

    Menu *menu = Menu::create(startItem, settingItem, extItem, nullptr);
    menu->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 0.5f));
    menu->alignItemsVertically();
    this->addChild(menu);

    return true;
}

void MenuScene::menuItemCallback(Ref *pSender)
{
    auto menuItem = static_cast<MenuItem *>(pSender);
    if( !menuItem )
        return;

    int tag = menuItem->getTag();
    switch( tag )
    {
    case StartTag:
    {
        auto transiton = TransitionShrinkGrow::create(0.5f, PreLoadScene::createScene());
        Director::getInstance()->replaceScene(transiton);
    };
        break;

    case SettingTag:
    {
    };
        break;
    case ExitTag:
    {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    };
        break;

    default: return;
    }
}

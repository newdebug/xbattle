/**
 * @description Project created by QtCreator.
 * @date 2017-11-28
 * @filename PreLoadScene.cpp
 * @class PreLoadScene
 * @author Yuri Young<yuri.young@qq.com>
 * @qq 12319597
 * Copyright (c) 2017 Yuri Young, All rights reserved.
 */

#include "PreLoadScene.h"
#include "GameScene.h"

#include <SimpleAudioEngine.h>

USING_NS_CC;
using namespace CocosDenshion;

PreLoadScene::PreLoadScene()
    : m_sourceCount(0),
      m_progressInterval(0.0f)
{

}

cocos2d::Scene *PreLoadScene::createScene()
{
    return PreLoadScene::create();
}

bool PreLoadScene::init()
{
    if( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    // create color background
    auto colorLayer = LayerColor::create(Color4B(48, 0, 71, 255));
    this->addChild(colorLayer, -999);

    auto strings = FileUtils::getInstance()->getValueMapFromFile("lang/chinese_simple.plist");
    m_loadingLabel = Label::createWithTTF(strings["loading"].asString(), "fonts/PangYuTou.ttf", 24);
    m_loadingLabel->setPosition(visibleSize / 2);

    Sprite* progressbarSprite = Sprite::create("images/progress.png");
    m_progress = ProgressTimer::create(progressbarSprite);
    m_progress->setPercentage(0.0f);

    // 设置进度条动画的起始位置，默认在图片的中点
    // 如果想要显示从左到右的一个动画效果，必须改成Vec2(0.0f, y)
    m_progress->setMidpoint(Vec2(0.0f, 0.5f));
    m_progress->setBarChangeRate(Vec2(1.0f, 0.0f));
    m_progress->setPosition(m_loadingLabel->getPositionX(),
                            m_loadingLabel->getPositionY() - m_loadingLabel->getContentSize().height);

    this->addChild(m_loadingLabel);
    this->addChild(m_progress);
    return true;
}

void PreLoadScene::loadMusic(const cocos2d::ValueVector &musicFiles)
{

}

void PreLoadScene::loadEffect(const cocos2d::ValueVector &effectFiles)
{
    for(size_t i = 0; i != effectFiles.size(); ++i)
    {
        cocos2d::Value val = effectFiles.at(i);
        std::string file = val.asString();
        SimpleAudioEngine::getInstance()->preloadEffect(file.c_str());
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
        this->progressUpdate();
    }
}

void PreLoadScene::loadSpriteSheets(const cocos2d::ValueVector &spriteSheets)
{

}

void PreLoadScene::progressUpdate()
{
    if(--m_sourceCount)
    {
        m_progress->setPercentage(100.0f - (m_progressInterval * m_sourceCount));
    }
    else
    {
        ProgressFromTo *fromTo =  ProgressFromTo::create(0.5f, m_progress->getPercentage(), 100.0f);
        CallFunc *replaceFn = CallFunc::create([=]{
            // 延迟1秒跳转到主场景
            DelayTime *delay = DelayTime::create(1.0f);
            CallFunc *delayFn = CallFunc::create([]{
                auto transition = TransitionPageTurn::create(0.5f, GameScene::createScene(), false);
                Director::getInstance()->replaceScene(transition);
            });
            Sequence *action = Sequence::create(delay, delayFn, nullptr);
            this->runAction(action);
        });
        Sequence* action = Sequence::create(fromTo, replaceFn, nullptr);
        m_progress->runAction(action);

        auto strings = FileUtils::getInstance()->getValueMapFromFile("lang/chinese_simple.plist");
        m_loadingLabel->setString(strings["loaded"].asString());
    }
}

void PreLoadScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();

    ValueMap resoucesMap = FileUtils::getInstance()->getValueMapFromFile("resources.plist");
    ValueVector effects = resoucesMap.at("Sounds").asValueVector();
    // TODO: reads other resources
    //...

    // TODO: adds other resources counts
    m_sourceCount = effects.size();
    m_progressInterval = 100.0f / m_sourceCount;

    this->loadEffect(effects);
    // TODO: loads other resources
}

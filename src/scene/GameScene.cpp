#include <SimpleAudioEngine.h>

#include "MenuScene.h"
#include "GameScene.h"
#include "MissionLayer.h"
#include "TerrainLayer.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto strings = FileUtils::getInstance()->getValueMapFromFile("lang/chinese_simple.plist");

    auto label = Label::createWithTTF("Cocos2dx in Qt", "fonts/Stripes_and_bubbles.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Stripes_and_bubbles.ttf'");
        return false;
    }

        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height - label->getContentSize().height));
        this->addChild(label, 1);

    auto backLabel = Label::createWithTTF(strings["backhome"].asString(), "fonts/PangYuTou.ttf", 24);
    auto backItem = MenuItemLabel::create(backLabel, CC_CALLBACK_1(GameScene::menuCallback, this));
    Size size = backItem->getContentSize();
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(size.width / 2, visibleSize.height - size.height / 2);
    this->addChild(menu, 1);

    TerrainLayer *terrain = TerrainLayer::create();
    MissionLayer *missionLayer = MissionLayer::create();
    missionLayer->setGameScene(this);
    this->addChild(terrain, -999);
    this->addChild(missionLayer);

    return true;
}

float GameScene::noise(int x, int y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.0 - ((n * ((n * n * 15731) + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

void GameScene::shakeScreen()
{
    //experiment more with these four values to get a rough or smooth effect!
    float interval = 0.f;
    float duration = 0.5f;
    float speed = 2.0f;
    float magnitude = 2.0f;

    static float elapsed = 0.f;

    this->schedule([=](float dt)
    {
        float randomStart = random(-1000.0f, 1000.0f);
        elapsed += dt;

        float percentComplete = elapsed / duration;

        // We want to reduce the shake from full power to 0 starting half way through
        float damper = 1.0f - clampf(2.0f * percentComplete - 1.0f, 0.0f, 1.0f);

        // Calculate the noise parameter starting randomly and going as fast as speed allows
        float alpha = randomStart + speed * percentComplete;

        // map noise to [-1, 1]
        float x = noise(alpha, 0.0f) * 2.0f - 1.0f;
        float y = noise(0.0f, alpha) * 2.0f - 1.0f;

        x *= magnitude * damper;
        y *= magnitude * damper;
        this->setPosition(x, y);

        if (elapsed >= duration)
        {
            elapsed = 0;
            this->unschedule("Shake");
            this->setPosition(Vec2::ZERO);
        }

    }, interval, CC_REPEAT_FOREVER, 0.f, "Shake");
}

void GameScene::menuCallback(Ref* pSender)
{
//    auto transition = TransitionFlipY::create(1.0f, MenuScene::createScene());
    auto transition = TransitionPageTurn::create(0.5f, MenuScene::createScene(), true);
    Director::getInstance()->replaceScene(transition);
}

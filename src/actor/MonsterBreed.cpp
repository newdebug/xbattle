#include "MonsterBreed.h"
#include "Monster.h"
#include "Actor3D.h"

USING_NS_CC;

MonsterBreed::MonsterBreed()
{
}

MonsterBreed::~MonsterBreed()
{
}

bool MonsterBreed::init()
{
    const std::string filename = "sprites/1.c3t";
    if( !FileUtils::getInstance()->isFileExist(filename) )
    {
#if COCOS2D_DEBUG
    char msg[256] = { 0 };
    sprintf(msg, "[MonsterBreed] Invalid sprite filename: %s", filename);
    CCASSERT(FileUtils::getInstance()->isFileExist(filename), msg);
#endif
        return false;
    }

    this->setFilename(filename);

    m_shaderCache = GLProgramCache::getInstance();

    return true;
}

Actor *MonsterBreed::createActor()
{
    if( this->init() )
    {
        Monster *monster = Monster::create(this);
        return monster;
    }

    return nullptr;
}

Actor3D *MonsterBreed::createActor3D()
{
    if( this->init() )
    {
        Actor3D *monster = Actor3D::create(this);
        this->addShader(monster, "color");
        return monster;
    }

    return nullptr;
}

Actor3D *MonsterBreed::createMonster()
{
    // breed由Actor内部增加/递减引用次数并释放内存
    MonsterBreed *breed = new MonsterBreed;// 这里引用次数已增加1
    breed->autorelease();
    return breed->createActor3D();
}

cocos2d::Vector<Actor3D *> MonsterBreed::createMonsters(int count)
{
    // breed由Actor内部增加/递减引用次数并释放内存
    MonsterBreed *breed = new MonsterBreed;
    breed->autorelease();
    cocos2d::log("[MonsterBreed]ref count retain: %d", breed->getReferenceCount());

    Vector<Actor3D *> monsters(count);
    for(int i = 0; i < count; ++i)
    {
        monsters.pushBack(breed->createActor3D());
    }
    return monsters;
}

void MonsterBreed::addShader(Actor3D *sprite3d, const std::string &shaderKey)
{
    GLProgram *shader = m_shaderCache->getGLProgram(shaderKey.c_str());
    if (!shader)
    {
        shader = GLProgram::createWithFilenames("shaders/" + shaderKey + ".vert", "shaders/" + shaderKey + ".frag");
    }
    else
    {
        m_shaderCache->addGLProgram(shader, shaderKey);
    }

    sprite3d->setBlendFunc(BlendFunc::ADDITIVE);
    auto shaderState = GLProgramState::getOrCreateWithGLProgram(shader);
    sprite3d->setGLProgramState(shaderState);

    Size size = sprite3d->getContentSize();
    auto scale_factor = Director::getInstance()->getContentScaleFactor();
    Vec3 resolution = Vec3(size.width, size.height, scale_factor);

    //shaderState->setUniformVec3("iResolution", resolution);
}

int MonsterBreed::role() const
{
    // always returns monster role.
    return ActorBreed::MonsterRole;
}

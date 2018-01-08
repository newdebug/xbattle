#include "TerrainLayer.h"

USING_NS_CC;

TerrainLayer::TerrainLayer()
	: m_background(nullptr)
{
	m_winSize = Director::getInstance()->getWinSize();
}

TerrainLayer::~TerrainLayer()
{
}

bool TerrainLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->scheduleUpdate();
	m_shaderCache = GLProgramCache::getInstance();

    const float w = m_winSize.width;
    const float h = m_winSize.height;

	m_background = Sprite::create();
	m_background->setContentSize(Size(w, h));
	m_background->setTextureRect(Rect(0, 0, w, h));
	m_background->setPosition(w / 2, h / 2);

    m_sprite = Sprite::create();
    m_sprite->setContentSize(Size(256, 256));
    m_sprite->setTextureRect(Rect(0, 0, 128, 128));
    m_sprite->setPosition(w / 2, h / 2);

    this->addShader(m_background, "sky");
    this->addShader(m_sprite, "buckyball");

    this->addChild(m_background, -999);
    this->addChild(m_sprite);

	return true;
}

void TerrainLayer::addShader(cocos2d::Sprite *sprite, const std::string &shaderKey)
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
	// 不是必须的
	//shader->link();
	//shader->updateUniforms();
	//shader->use();

	sprite->setBlendFunc(BlendFunc::ADDITIVE);
	auto shaderState = GLProgramState::getOrCreateWithGLProgram(shader);
	sprite->setGLProgramState(shaderState);

	auto size = sprite->getTexture()->getContentSizeInPixels();
	// 没有纹理的精灵，默认最小为2的一次方
	size = size.width < 4 || size.height < 4 ? sprite->getContentSize() : size;
	auto scale_factor = Director::getInstance()->getContentScaleFactor();
	Vec3 resolution = Vec3(size.width, size.height, scale_factor);

	shaderState->setUniformVec3("iResolution", resolution);
}

void TerrainLayer::addShader(cocos2d::Sprite *sprite, const std::string &shaderKey, const std::string &channel)
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

	sprite->setBlendFunc(BlendFunc::ADDITIVE);
	auto shaderState = GLProgramState::getOrCreateWithGLProgram(shader);
	sprite->setGLProgramState(shaderState);

	auto size = sprite->getTexture()->getContentSizeInPixels();
	size = size.width < 4 || size.height < 4 ? sprite->getContentSize() : size;
	auto texture = Director::getInstance()->getTextureCache()->addImage(channel);
	auto texturesize = texture->getContentSizeInPixels();
	auto scale_factor = Director::getInstance()->getContentScaleFactor();
	Vec3 resolution = Vec3(size.width, size.height, scale_factor);

	shaderState->setUniformVec3("iResolution", resolution);
	shaderState->setUniformTexture("iChannel0", texture);
	shaderState->setUniformVec2("iChannelResolution", texturesize);
}

void TerrainLayer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	m_customCommand.init(_globalZOrder - 10);
    m_customCommand.func = CC_CALLBACK_0(TerrainLayer::onDraw, this, transform, flags);
	renderer->addCommand(&m_customCommand);
}

void TerrainLayer::onDraw(const Mat4 &transform, uint32_t flags)
{
	// TODO: opengl draw here
	// 每帧都会调用
}



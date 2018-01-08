#ifndef TERRAINLAYER_h
#define TERRAINLAYER_h

#include <cocos2d.h>

class TerrainLayer : public cocos2d::Layer
{
public:
	TerrainLayer();
	~TerrainLayer();
	void addShader(cocos2d::Sprite *sprite, const std::string &shaderKey);
	void addShader(cocos2d::Sprite *sprite, const std::string &shaderKey, const std::string &channel);

    CREATE_FUNC(TerrainLayer)

protected:
	/*
	 * In future, cocos2d-x 3.x renderer will be multithreaded with command pool.
     * draw method called by visit method, to create new command. When command is
     * performed by command pool, onDraw is called. At this moment, commands are
     * performed in single thread, but in overloaded onDraw method you should assume,
     * that it will be called in another thread to simplify future migration.
	*/
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
	virtual void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);

private:
	virtual bool init() override;

private:
	cocos2d::Size m_winSize;
	cocos2d::Sprite* m_background;
    cocos2d::Sprite* m_sprite;
	cocos2d::CustomCommand m_customCommand;
	cocos2d::GLProgramCache* m_shaderCache;
};

#endif // TERRAINLAYER_h

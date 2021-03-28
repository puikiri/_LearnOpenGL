#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include "renderObject.h"

class RenderWorld
{
public:
	RenderWorld();
	~RenderWorld();

	inline void regRenderObject(const std::string &regId, std::shared_ptr<RenderObject> obj) { renderVec[regId] = obj; }
	inline void removeRenderObject(const std::string &regId) { renderVec.erase(regId); }
	void render();
private:

public:

private:
	std::map<std::string, std::shared_ptr<RenderObject>> renderVec;
};

RenderWorld::RenderWorld()
{
}

RenderWorld::~RenderWorld()
{
	renderVec.clear();
}

void RenderWorld::render()
{
	for (auto ro : renderVec)
		ro.second->draw();
}

#endif
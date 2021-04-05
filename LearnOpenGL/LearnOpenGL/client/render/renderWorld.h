#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include "renderObject.h"
#include "window.h"

class RenderWorld
{
public:
	RenderWorld();
	~RenderWorld();

	inline void regRenderObject(const std::string &regId, std::shared_ptr<RenderObject> obj) { renderVec[regId] = obj; }
	inline void removeRenderObject(const std::string &regId) { renderVec.erase(regId); }
	void render();
	const std::shared_ptr<Window> getWindow() const { return win; };
private:

public:

private:
	std::map<std::string, std::shared_ptr<RenderObject>> renderVec;
	std::shared_ptr<Window> win;
};

RenderWorld::RenderWorld()
{
	win = std::make_shared<Window>();
}

RenderWorld::~RenderWorld()
{
	win = nullptr;
	renderVec.clear();
}

void RenderWorld::render()
{
	for (auto ro : renderVec)
		ro.second->beforeRender();
	win->beforeRender();

	for (auto ro : renderVec)
		ro.second->render();
	win->render();

	for (auto ro : renderVec)
		ro.second->afterRender();
	win->afterRender();
}

#endif
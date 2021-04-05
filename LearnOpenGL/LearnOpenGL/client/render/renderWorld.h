#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include "renderObject.h"
#include "window.h"

class RenderWorld
{
public:
	static RenderWorld* instance()
	{
		if (!rw)
			rw = new RenderWorld();
		return rw;
	}
	~RenderWorld();
	void operator=(const RenderWorld &) = delete;

	inline void regRenderObject(const std::string &regId, std::shared_ptr<RenderObject> obj) { renderVec[regId] = obj; }
	inline void removeRenderObject(const std::string &regId) { renderVec.erase(regId); }
	void render();
private:
	RenderWorld();

public:

private:
	std::map<std::string, std::shared_ptr<RenderObject>> renderVec;
	Window* win;
	static RenderWorld* rw;
};

RenderWorld::RenderWorld()
{
	win = Window::instance();
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

RenderWorld* RenderWorld::rw = nullptr;
#endif
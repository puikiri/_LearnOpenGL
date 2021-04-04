#ifndef RENDER_BASE_H
#define RENDER_BASE_H

class RenderBase
{
public:
	RenderBase() {};
	virtual ~RenderBase() {};

	virtual void beforeRender() = 0;
	virtual void render() = 0;
	virtual void afterRender() = 0;
private:

public:

private:

};

#endif
#ifndef RENDER_H
#define RENDER_H

#include <functional>

#include "../../core/include.h"
#include "renderWorld.h"

typedef void(*WinSizeCallback)(int, int);
typedef void(*WinKeyEnterCallback)(int, int, int, int);

static std::map<std::string, std::function<void(int, int)>> winSizeCallBackMap;
static void onSize(GLFWwindow* window, int width, int height)
{
	printf(" what the hell?! why change the win size !!!!! width %d, height %d .  \
		\n ola ola ola ola ola ola ola ola ola ola ola ola ola ola ola ola ola !!!!! \n", width, height);
	glViewport(0, 0, width, height);
	for (auto it : winSizeCallBackMap)
		it.second(width, height);
}

static std::map<std::string, std::function<void(int, int, int, int)>> winKeyEnterCallbackMap;
static void onEnter(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	printf(" what's this?! key %d, scancode %d, action %d, mods %d !!!!!  \
		\n muda muda muda muda muda muda muda muda muda muda muda muda !!!!! \n", key, scancode, action, mods);
	for (auto it : winKeyEnterCallbackMap)
		it.second(key, scancode, action, mods);
}

class Render
{
public:
	Render();
	~Render();

	inline void RegWinSizeCallBack(const std::string &regId, WinSizeCallback& func) 
	{
		if (winSizeCallBackMap.find(regId) != winSizeCallBackMap.end())
		{
			printf(" repeat reg a callback func, id : %s ", regId.c_str());
			return;
		}
		winSizeCallBackMap[regId] = func;
	};
	inline void RegWinKeyEnterCallBack(const std::string &regId, WinKeyEnterCallback& func)
	{
		if (winKeyEnterCallbackMap.find(regId) != winKeyEnterCallbackMap.end())
		{
			printf(" repeat reg a callback func, id : %s ", regId.c_str());
			return;
		}
		winKeyEnterCallbackMap[regId] = func;
	};
	inline void DelWinSizeCallBack(const std::string &regId) { winSizeCallBackMap.erase(regId); }
	inline void DelWinKeyEnterCallBack(const std::string &regId) { winKeyEnterCallbackMap.erase(regId); }
	void draw();
	std::shared_ptr<RenderWorld> gerRenderWorld() { return renderWorld; };
private:
	GLFWwindow* getWin();

	void prepareScene();
	void renderScene();
	void afterRender();

	void clearSceneColor();
public:

private:
	GLFWwindow* win;
	std::shared_ptr<RenderWorld> renderWorld;
};

Render::Render()
{
	win = getWin();
	Assert(win, " what the fuck glfwWin ?! \n");
	//assert(win);
	glfwMakeContextCurrent(win);
	Assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), " what the fuck glad ?! \n");
	//assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
	glViewport(0, 0, winSizeW, winSizeH);
	glfwSetFramebufferSizeCallback(win, onSize);
	glfwSetKeyCallback(win, onEnter);

	glEnable(GL_DEPTH_TEST); // 启用深度缓冲测试

	renderWorld = std::make_shared<RenderWorld>();
}

Render::~Render()
{
	renderWorld = nullptr;
	glfwTerminate();
}

GLFWwindow* Render::getWin()
{
	glfwInit();
	// 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwVerMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwVerMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return glfwCreateWindow(winSizeW, winSizeH, "Jojo,O re no nin ge da !!!!!", NULL, NULL);
}

void Render::clearSceneColor()
{
	glClearColor(glfwClearColor);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::prepareScene()
{
	clearSceneColor();
}

void Render::renderScene()
{
	renderWorld->render();
}

void Render::afterRender()
{
	glfwPollEvents();
	glfwSwapBuffers(win);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 每帧结束清楚深度缓冲
}

void Render::draw()
{
	prepareScene();
	renderScene();
	afterRender();
}
#endif
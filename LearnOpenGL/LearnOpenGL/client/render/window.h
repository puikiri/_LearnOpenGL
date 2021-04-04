#ifndef WINDOW_H
#define WINDOW_H

#include <functional>

#include "../../core/include.h"
#include "renderBase.h"

typedef void(*WinSizeCallback)(int, int);
typedef void(*WinKeyEnterCallback)(int, int, int, int);
typedef void(*WinCursorChangeCallback)(double, double);
typedef void(*WinScrollCallback)(double, double);

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

static std::map<std::string, std::function<void(double, double)>> winCursorChangeCallbackMap;
static void onCursorChange(GLFWwindow* window, double xpos, double ypos)
{
	printf(" what's this?! xpos %f, xpos %f, !!!!!  \
		\n dio da dio da dio da dio da dio da dio da dio da dio da dio da !!!!! \n", xpos, ypos);
	for (auto it : winCursorChangeCallbackMap)
		it.second(xpos, ypos);
}

static std::map<std::string, std::function<void(double, double)>> winScrollChangeCallbackMap;
void onScrollChange(GLFWwindow* window, double xoffset, double yoffset)
{
	printf(" what's this?! xoffset %f, yoffset %f, !!!!!  \
		\n JOJO JOJO JOJO JOJO JOJO JOJO JOJO JOJO JOJO JOJO JOJO !!!!! \n", xoffset, yoffset);
	for (auto it : winScrollChangeCallbackMap)
		it.second(xoffset, yoffset);
}
class Window :public virtual RenderBase
{
public:
	Window();
	~Window();

	inline void RegWinSizeCallBack(const std::string &regId, WinSizeCallback func)
	{
		if (winSizeCallBackMap.find(regId) != winSizeCallBackMap.end())
		{
			printf(" repeat reg a RegWinSizeCallBack func, id : %s ", regId.c_str());
			return;
		}
		winSizeCallBackMap[regId] = func;
	};
	inline void RegWinKeyEnterCallBack(const std::string &regId, WinKeyEnterCallback func)
	{
		if (winKeyEnterCallbackMap.find(regId) != winKeyEnterCallbackMap.end())
		{
			printf(" repeat reg a RegWinKeyEnterCallBack func, id : %s ", regId.c_str());
			return;
		}
		winKeyEnterCallbackMap[regId] = func;
	};
	inline void RegWinCursorChangeCallBack(const std::string &regId, WinCursorChangeCallback func)
	{
		if (winCursorChangeCallbackMap.find(regId) != winCursorChangeCallbackMap.end())
		{
			printf(" repeat reg a RegWinCursorChangeCallBack func, id : %s ", regId.c_str());
			return;
		}
		winCursorChangeCallbackMap[regId] = func;
	};
	inline void RegWinScrollCallBack(const std::string &regId, WinScrollCallback func)
	{
		if (winScrollChangeCallbackMap.find(regId) != winScrollChangeCallbackMap.end())
		{
			printf(" repeat reg a callback func, id : %s ", regId.c_str());
			return;
		}
		winScrollChangeCallbackMap[regId] = func;
	};
	inline void DelWinSizeCallBack(const std::string &regId) { winSizeCallBackMap.erase(regId); }
	inline void DelWinKeyEnterCallBack(const std::string &regId) { winKeyEnterCallbackMap.erase(regId); }
	inline void DelWinCursorChangeCallBack(const std::string &regId) { winCursorChangeCallbackMap.erase(regId); }
	inline void DelWinScrollCallBack(const std::string &regId) { winScrollChangeCallbackMap.erase(regId); }

	virtual void beforeRender();
	virtual void render();
	virtual void afterRender();
private:
	GLFWwindow* getWin();

	void clearSceneColor();
public:

private:
	GLFWwindow* win;
};

Window::Window()
{
	win = getWin();
	Assert(win, " what the fuck ? create glfwWin error ?! \n");
	glfwMakeContextCurrent(win);
	Assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), " what the fuck ? create glad error?! \n");
	glViewport(0, 0, winSizeW, winSizeH);

	glfwSetFramebufferSizeCallback(win, onSize);
	glfwSetKeyCallback(win, onEnter);
	glfwSetCursorPosCallback(win, onCursorChange);
	glfwSetScrollCallback(win, onScrollChange);

	glEnable(GL_DEPTH_TEST); // 启用深度缓冲测试
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 启用游标
}

Window::~Window()
{
	glfwTerminate();
}

GLFWwindow* Window::getWin()
{
	glfwInit();
	// 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwVerMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwVerMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return glfwCreateWindow(winSizeW, winSizeH, "Jojo,O re no nin ge da !!!!!", NULL, NULL);
}

void Window::clearSceneColor()
{
	glClearColor(glfwClearColor);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::beforeRender()
{
	clearSceneColor();
}

void Window::render()
{
}

void Window::afterRender()
{
	/* call event */
	glfwPollEvents();
	/* switch buff */
	glfwSwapBuffers(win);
	/*  每帧结束清除深度缓冲 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

#endif

#include "client/render/renderWorld.h"
#include "client/render/renderObject.h"
#include "client/render/textureManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool loop = true;
bool checkLoop()
{
	return loop;
}

void setLoop(bool lp)
{
	loop = lp;
}

//float vertices1[] = {
//	-0.4f, -0.4f, 0.0f, 0.0f, 0.0f, 1.0f,
//	0.4f, -0.4f, 0.0f, 0.0f, 1.0f, 0.0f,
//	0.f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f,
//	-0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
//	0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f,
//	0.f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f,
//};
//
//unsigned int vertices1indices[] = {
//	0, 1, 2,
//	3, 4, 5,
//};

float vertices1[] = { 
	// vec的位置			color			texture的位置。 注：texture和vec的是上下左右颠倒的 
	// 或者在加载图片时使用 stbi_set_flip_vertically_on_load(true); 翻转一下
	// 或者直接在vs里面把y翻转处理  TexCoord = vec2(inTexCoord.x, 1.0 - inTexCoord.y);
	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,


	-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,   0.0f, 0.0f,
};

unsigned int vertices1indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3,  // second triangle
		4, 5, 7,
		5, 6, 7,
		8, 9, 11,
		9, 10, 11,
		12, 13, 15,
		13, 14, 15,
		16, 17, 19,
		17, 18, 19,
		20, 21, 23,
		21, 22, 23,
};

int cubeNum = 10;
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  1.0f, -1.0f)
};

///* camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

bool firstMouse = true;
float yaw = -90;
float pitch = 0;
float fov = 45.f;
void processInput(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		setLoop(false);
	float cameraSpeed = 5.f * deltaTime; // adjust accordingly
	if (key == GLFW_KEY_W && action != GLFW_RELEASE)
		cameraPos += cameraSpeed * cameraFront;
	if (key == GLFW_KEY_S && action != GLFW_RELEASE)
		cameraPos -= cameraSpeed * cameraFront;
	if (key == GLFW_KEY_A && action != GLFW_RELEASE)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (key == GLFW_KEY_D && action != GLFW_RELEASE)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (key == GLFW_KEY_R && action != GLFW_RELEASE)
	{
		cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		firstMouse = true;
		yaw = -90;
		pitch = 0;
	}
}

float lastX = winSizeW/2, lastY = winSizeH/2;
float sensitivity = 0.05f;
void cursorChangeCb(double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xPos;
	lastY = yPos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

void scrollChange(double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= viewFov)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= viewFov)
		fov = viewFov;
}
int main()
{
	RenderWorld* render = RenderWorld::instance();
	Window* window = Window::instance();
	window->RegWinKeyEnterCallBack("processInput", processInput);
	window->RegWinCursorChangeCallBack("cursorChangeCb", cursorChangeCb);
	window->RegWinScrollCallBack("scrollChange", scrollChange);
	// TODO RE CODE

	///* 视口
	/*
		local * modelMat => world * viewMat => view * projectionMat => clip * viewportMat => screen  
		局部坐标是对象相对于局部原点的坐标，也是物体起始的坐标。
		下一步是将局部坐标变换为世界空间坐标，世界空间坐标是处于一个更大的空间范围的。这些坐标相对于世界的全局原点，它们会和其它物体一起相对于世界的原点进行摆放。
		接下来我们将世界坐标变换为观察空间坐标，使得每个坐标都是从摄像机或者说观察者的角度进行观察的。
		坐标到达观察空间之后，我们需要将其投影到裁剪坐标。裁剪坐标会被处理至-1.0到1.0的范围内，并判断哪些顶点将会出现在屏幕上。
		最后，我们将裁剪坐标变换为屏幕坐标，我们将使用一个叫做视口变换(Viewport Transform)的过程。视口变换将位于-1.0到1.0范围的坐标变换到由glViewport函数所定义的坐标范围内。最后变换出来的坐标将会送到光栅器，将其转化为片段。
	*/
	// glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // 正射投影矩阵
	//										视角							宽高比			近/远平面
	//			近平面太大的话 会导致一个在游戏中很熟悉的视觉效果：在太过靠近一个物体的时候，视线会直接穿过去。
	//			远平面太大的话 会导致计算量激增。
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(viewFov), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 projectionMat = glm::perspective(glm::radians(viewFov), (float)winSizeW / (float)winSizeH, viewZNear, viewZFar);

	///* shader
	std::shared_ptr<Shader> shader = std::make_shared<Shader>("../LearnOpenGL/resource/shader/box.vs", "../LearnOpenGL/resource/shader/box.fs");
	for (int i = 0; i < cubeNum; i++)
	{
	std::shared_ptr<RenderObject> ro2 = std::make_shared<RenderObject>(shader);
	ro2->createEBORenderObject(vertices1, sizeof(vertices1), vertices1indices, sizeof(vertices1indices), 0, 3, false, 8, 0);
	ro2->attachVertexAttribPointer(1, 3, false, 8, 3);
	ro2->attachVertexAttribPointer(2, 2, false, 8, 6);
	ro2->setDrawVerNum(36);
	ro2->setPosition(cubePositions[i]);
	render->regRenderObject(ro2->getName(), ro2);
	}

	///* texture
	shader->setTexture(0, "baseTexture", "../LearnOpenGL/resource/texture/texture_unhell.png");
	shader->setTexture(1, "mixTexture", "../LearnOpenGL/resource/texture/texture_unhell_tag.png");

	while (checkLoop())
	{
		float timeValue = glfwGetTime();
		auto temp = sin(timeValue);

		///* color
		int vertexColorLocation = glGetUniformLocation(shader->getID(), "muxColor");
		glUniform4f(vertexColorLocation, temp + 0.1, temp, temp - 0.1, (temp / 2.0f));

		///* transform
		auto temp2 = sin(timeValue / 5);

		deltaTime = timeValue - lastFrame;
		lastFrame = timeValue;

		glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		projectionMat = glm::perspective(glm::radians(fov), (float)winSizeW / (float)winSizeH, viewZNear, viewZFar);

		for (auto temp : render->getRenderObjects())
		{
			glm::mat4 trans = glm::mat4(1.0f);
			trans = glm::translate(trans, temp.second->getPosition()); // 前后顺序是有影响的。变现是从下到上矩阵相乘。
			trans = glm::rotate(trans, timeValue, glm::vec3(1.0, 1.0, 1.0));
			trans = glm::scale(trans, glm::vec3(temp2, temp2, temp2));
			//trans = glm::translate(trans, temp.second->getPosition());
			auto t = projectionMat * viewMat * modelMat * trans;
			temp.second->setTransformMat(t);
		}

		render->render();
	}
	return -1;
}

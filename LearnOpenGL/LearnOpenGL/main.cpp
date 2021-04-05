
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
	// vec��λ��			color			texture��λ�á� ע��texture��vec�����������ҵߵ��� 
	// �����ڼ���ͼƬʱʹ�� stbi_set_flip_vertically_on_load(true); ��תһ��
	// ����ֱ����vs�����y��ת����  TexCoord = vec2(inTexCoord.x, 1.0 - inTexCoord.y);
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
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

///* camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

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
	float yoffset = lastY - yPos; // ע���������෴�ģ���Ϊy�����Ǵӵײ����������������
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
	render->getWindow()->RegWinKeyEnterCallBack("processInput", processInput);
	render->getWindow()->RegWinCursorChangeCallBack("cursorChangeCb", cursorChangeCb);
	render->getWindow()->RegWinScrollCallBack("scrollChange", scrollChange);
	// TODO RE CODE

	///* �ӿ�
	/*
		local * modelMat => world * viewMat => view * projectionMat => clip * viewportMat => screen  
		�ֲ������Ƕ�������ھֲ�ԭ������꣬Ҳ��������ʼ�����ꡣ
		��һ���ǽ��ֲ�����任Ϊ����ռ����꣬����ռ������Ǵ���һ������Ŀռ䷶Χ�ġ���Щ��������������ȫ��ԭ�㣬���ǻ����������һ������������ԭ����аڷš�
		���������ǽ���������任Ϊ�۲�ռ����꣬ʹ��ÿ�����궼�Ǵ����������˵�۲��ߵĽǶȽ��й۲�ġ�
		���굽��۲�ռ�֮��������Ҫ����ͶӰ���ü����ꡣ�ü�����ᱻ������-1.0��1.0�ķ�Χ�ڣ����ж���Щ���㽫���������Ļ�ϡ�
		������ǽ��ü�����任Ϊ��Ļ���꣬���ǽ�ʹ��һ�������ӿڱ任(Viewport Transform)�Ĺ��̡��ӿڱ任��λ��-1.0��1.0��Χ������任����glViewport��������������귶Χ�ڡ����任���������꽫���͵���դ��������ת��ΪƬ�Ρ�
	*/
	// glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // ����ͶӰ����
	//										�ӽ�							��߱�			��/Զƽ��
	//			��ƽ��̫��Ļ� �ᵼ��һ������Ϸ�к���Ϥ���Ӿ�Ч������̫������һ�������ʱ�����߻�ֱ�Ӵ���ȥ��
	//			Զƽ��̫��Ļ� �ᵼ�¼�����������
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(viewFov), glm::vec3(1.0f, 0.0f, 0.0f));
	/*glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));*/
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
	glm::mat4 tempMat = glm::mat4(1.0f);
	tempMat = glm::translate(tempMat, cubePositions[i]);
	ro2->setExTransformMat(tempMat);
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
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, timeValue, glm::vec3(1.0, 1.0, 1.0));
		trans = glm::scale(trans, glm::vec3(temp2, temp2, temp2));
		shader->setMat4("boxTransform", trans);


		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		projectionMat = glm::perspective(glm::radians(fov), (float)winSizeW / (float)winSizeH, viewZNear, viewZFar);

		shader->setMat4("modelMat", modelMat);
		shader->setMat4("viewMat", viewMat);
		shader->setMat4("projectionMat", projectionMat);

		render->render();
	}
	return -1;
}

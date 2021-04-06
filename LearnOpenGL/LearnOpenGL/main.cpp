
#include "client/render/renderWorld.h"
#include "client/render/renderObject.h"
#include "client/render/textureManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

bool loop = true;
bool checkLoop()
{
	return loop;
}

void setLoop(bool lp)
{
	loop = lp;
}

float vertices2[] = {
	// vec��λ��			color			texture��λ�á� ע��texture��vec�����������ҵߵ��� 
	// �����ڼ���ͼƬʱʹ�� stbi_set_flip_vertically_on_load(true); ��תһ��
	// ����ֱ����vs�����y��ת����  TexCoord = vec2(inTexCoord.x, 1.0 - inTexCoord.y);
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,   0.0f, 1.0f,


	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,   0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,   1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,   0.0f, 0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
};

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

std::vector<glm::vec3> cubePositions;

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
	/* box
	cubePositions.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
	cubePositions.emplace_back(glm::vec3(0.0f, 4.0f, 0.0f));
	cubePositions.emplace_back(glm::vec3(0.0f, -4.0f, 0.0f));
	cubePositions.emplace_back(glm::vec3(2.0f, 0.0f, 0.0f));
	cubePositions.emplace_back(glm::vec3(4.0f, 0.0f, 0.0f));
	cubePositions.emplace_back(glm::vec3(-2.0f, 0.0f, 0.0f));
	cubePositions.emplace_back(glm::vec3(-4.0f, 0.0f, 0.0f));
	int cubeNum = cubePositions.size();
	*/
	RenderWorld* render = RenderWorld::instance();
	Window* window = Window::instance();
	window->RegWinKeyEnterCallBack("processInput", processInput);
	window->RegWinCursorChangeCallBack("cursorChangeCb", cursorChangeCb);
	window->RegWinScrollCallBack("scrollChange", scrollChange);
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
	glm::mat4 projectionMat = glm::perspective(glm::radians(viewFov), (float)winSizeW / (float)winSizeH, viewZNear, viewZFar);
	/* box
	///* box
	std::map<std::string, std::shared_ptr<RenderObject>> boxRenderVecs;
	std::shared_ptr<Shader> boxShader = std::make_shared<Shader>("../LearnOpenGL/resource/shader/box.vs", "../LearnOpenGL/resource/shader/box.fs");
	for (int i = 0; i < cubeNum; i++)
	{
		std::shared_ptr<RenderObject> ro2 = std::make_shared<RenderObject>(boxShader);
		ro2->createEBORenderObject(vertices1, sizeof(vertices1), vertices1indices, sizeof(vertices1indices), 0, 3, false, 8, 0);
		ro2->attachVertexAttribPointer(1, 3, false, 8, 3);
		ro2->attachVertexAttribPointer(2, 2, false, 8, 6);
		ro2->setDrawVerNum(36);
		ro2->setPosition(cubePositions[i]);
		render->regRenderObject(ro2->getName(), ro2);
		boxRenderVecs[ro2->getName()] = ro2;
	}
	boxShader->setTexture(0, "baseTexture", "../LearnOpenGL/resource/texture/texture_unhell.png");
	boxShader->setTexture(1, "mixTexture", "../LearnOpenGL/resource/texture/texture_unhell_tag.png");
	*/

	///* sunLight
	std::shared_ptr<Shader> sunLightShader = std::make_shared<Shader>("../LearnOpenGL/resource/shader/light.vs", "../LearnOpenGL/resource/shader/light.fs");
	std::shared_ptr<RenderObject> ao3 = std::make_shared<RenderObject>(sunLightShader);
	ao3->createEBORenderObject(vertices2, sizeof(vertices2), vertices1indices, sizeof(vertices1indices), 0, 3, false, 8, 0);
	ao3->attachVertexAttribPointer(1, 3, false, 8, 3);
	ao3->attachVertexAttribPointer(2, 2, false, 8, 6);
	ao3->setDrawVerNum(36);
	ao3->setPosition(glm::vec3(2.0f, 2.0f, 2.0f));
	render->regRenderObject(ao3->getName(), ao3);
	sunLightShader->setTexture(0, "baseTexture", "../LearnOpenGL/resource/texture/sunLight.png");
	glm::mat4 ro3Trans = glm::mat4(1.0f);
	ro3Trans = glm::translate(ro3Trans, ao3->getPosition());
	ro3Trans = glm::scale(ro3Trans, glm::vec3(0.5, 0.5, 0.5));


	///* lightBox
	std::shared_ptr<Shader> lightBoxShader = std::make_shared<Shader>("../LearnOpenGL/resource/shader/lightBox.vs", "../LearnOpenGL/resource/shader/lightBox.fs");
	std::shared_ptr<RenderObject> ao4 = std::make_shared<RenderObject>(lightBoxShader);
	ao4->createEBORenderObject(vertices2, sizeof(vertices2), vertices1indices, sizeof(vertices1indices), 0, 3, false, 8, 0);
	ao4->attachVertexAttribPointer(1, 3, false, 8, 3);
	ao4->attachVertexAttribPointer(2, 2, false, 8, 6);
	ao4->setDrawVerNum(36);
	ao4->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	render->regRenderObject(ao4->getName(), ao4);
	lightBoxShader->setTexture(0, "baseTexture", "../LearnOpenGL/resource/texture/lightBox.png");
	glm::mat4 ro4Trans = glm::mat4(1.0f);
	ro4Trans = glm::translate(ro4Trans, ao4->getPosition());

	auto lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	sunLightShader->setVec4("lightColor", lightColor);
	auto objectColor = lightColor;
	lightBoxShader->setVec4("lightColor", lightColor);
	lightBoxShader->setVec4("objectColor", objectColor);
	lightBoxShader->setMat4("modelMat", modelMat);

	while (checkLoop())
	{
		float timeValue = glfwGetTime();
		auto sin_timeValue = sin(timeValue);
		auto sin_timeValue_2 = sin(timeValue / 5);
		auto cos_timeValue_2 = cos(timeValue / 5);

		deltaTime = timeValue - lastFrame;
		lastFrame = timeValue;

		glm::mat4 viewMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		projectionMat = glm::perspective(glm::radians(fov), (float)winSizeW / (float)winSizeH, viewZNear, viewZFar);

		auto color = glm::vec4(cos_timeValue_2, sin_timeValue, sin_timeValue_2, (sin_timeValue / 2.0f));
		// ao3 pos change 
		ro3Trans = glm::mat4(1.0f);
		auto pos = glm::vec3(2.0f * sin_timeValue_2, 2.0f * cos_timeValue_2, sin_timeValue * cos_timeValue_2);
		ao3->setPosition(pos);
		ro3Trans = glm::translate(ro3Trans, ao3->getPosition());
		ro3Trans = glm::scale(ro3Trans, glm::vec3(0.5, 0.5, 0.5));
		auto ro3Transform = projectionMat * viewMat * modelMat * ro3Trans;
		ao3->setTransformMat(ro3Transform);
		sunLightShader->setVec4("lightColor", color);

		auto ro4Transform = projectionMat * viewMat * modelMat * ro4Trans;
		ao4->setTransformMat(ro4Transform);
		lightBoxShader->setVec3("lightPos", ao3->getPosition());
		lightBoxShader->setVec4("lightColor", color);
		lightBoxShader->setVec3("viewPos", cameraPos);

		/*  box
		for (auto ro : boxRenderVecs)
		{
			glm::mat4 trans = glm::mat4(1.0f);
			//trans = glm::translate(trans, ro.second->getPosition()); // �任��ǰ��˳������Ӱ��ġ����µ��Ͼ�����ˡ�
			trans = glm::rotate(trans, timeValue, glm::vec3(1.0, 1.0, 1.0));
			trans = glm::scale(trans, glm::vec3(sin_timeValue_2, sin_timeValue_2, sin_timeValue_2));
			auto roPos = ro.second->getPosition();
			trans = glm::translate(trans, roPos);

			auto transform = projectionMat * viewMat * modelMat * trans;
			ro.second->setTransformMat(transform);

			auto color = glm::vec4(sin_timeValue + 0.1 + roPos.x / 10, sin_timeValue + roPos.y / 10, sin_timeValue - 0.1 + roPos.z / 10, (sin_timeValue / 2.0f));
			ro.second->setMuxColor(color);
		}
		*/
		render->render();
	}
	return -1;
}

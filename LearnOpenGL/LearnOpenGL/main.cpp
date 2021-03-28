
#include "client/render/render.h"
#include "client/render/renderObject.h"

#include <stb/stb_image.h>

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

int main()
{
	Render render;

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
	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projectionMat = glm::perspective(glm::radians(viewFov), (float)winSizeW / (float)winSizeH, viewZNear, viewZFar);

	///* shader
	std::shared_ptr<Shader> shader = std::make_shared<Shader>("../LearnOpenGL/resource/shader/box.vs", "../LearnOpenGL/resource/shader/box.fs");
	std::shared_ptr<RenderObject> ro2 = std::make_shared<RenderObject>(shader);
	ro2->createEBORenderObject(vertices1, sizeof(vertices1), vertices1indices, sizeof(vertices1indices), 0, 3, false, 8, 0);
	ro2->attachVertexAttribPointer(1, 3, false, 8, 3);
	ro2->attachVertexAttribPointer(2, 2, false, 8, 6);
	ro2->setDrawVerNum(36);
	render.gerRenderWorld()->regRenderObject(ro2->getName(), ro2);

	///* texture
	unsigned int texture[2];
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	// һ�� ָ��2d����Ϊ����
	// ���� s => x�ᣬt => y�ᡣ
	// ���������� ���뷽ʽ��GL_REPEAT �ظ���GL_MIRRORED_REPEAT ����GL_CLAMP_TO_EDGE ��Ե���죬GL_CLAMP_TO_BORDER �����
	/*
		ʹ�� GL_CLAMP_TO_BORDER,����Ҫָ����Եɫ��ʹ�� glTexParameterfvָ��
			float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// ������ˣ���������/ѹ��������ȡ��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // �༶������
	/*
		�ڶ���������
			GL_TEXTURE_MIN_FILTER ѹ��/��С
			GL_TEXTURE_MAG_FILTER ����/�Ŵ�
		������������
			GL_NEAREST �������(ֻȡ��������)
			GL_LINEAR ���Թ���(ȡ��ֵ/�����)
			..
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels; // nrChannels ��ɫͨ����
	stbi_set_flip_vertically_on_load(true); // ͼƬ�������shader���������
	unsigned char *data = stbi_load("../LearnOpenGL/resource/texture/texture_unhell.png", &width, &height, &nrChannels, 0); 
	// ע�⣡���������пӣ������������ͼƬҪ������ͼƬ������png�ֶ��ĺ�׺��jpg�ǻ�����ģ�������������
	stbi_set_flip_vertically_on_load(false);
	unsigned int sourceColorType = GL_RGB;
	if (nrChannels == 4)
		sourceColorType = GL_RGBA;
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, sourceColorType, width, height, 0, sourceColorType, GL_UNSIGNED_BYTE, data);
		// ע�⣡���������пӣ�������Դͼ�ģ�sourceColorType��RGBA��ɫ/��ʽ֮���һ��Ҫ���ϣ���������Ȼ����ֺ���ֵ�ͼƬ(��һ����a����һ��rgbȡ����)
		/*
		Ŀ���������-�༶���伶��-��ɫģʽ-�����-��-����0-��������-����(load������ͼ������)
		*/
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("wocao ! where the jpg ??? \n");
	}
	stbi_image_free(data); // ����ͼ���shader��fs/vsһ���������ɾ(�Ѷ����ڴ�)��


	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("../LearnOpenGL/resource/texture/texture_unhell_tag.png", &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(false);
	sourceColorType = GL_RGB;
	if (nrChannels == 4)
		sourceColorType = GL_RGBA;
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, sourceColorType, width, height, 0, sourceColorType, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("wocao ! where the jpg mix??? \n");
	}
	stbi_image_free(data);

	// ���ö�����Ӧ�Ļ��
	shader->active(); // ע�⣬��Ҫ�ȼ���Ҫ���õ�shader�����ã���Ȼ�᲻֪�����õ�����ȥ��
	shader->setInt("baseTexture", 0);
	shader->setInt("mixTexture", 1);
	shader->deactive();
	// �������ͼ��ͬһ������Ԫ�ϣ�����ͬһ��fs�ϣ�
	glActiveTexture(GL_TEXTURE0);// �ڰ�����֮ǰ��Ҫ�ȼ�������Ԫ 
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	while (checkLoop())
	{
		float timeValue = glfwGetTime();
		auto temp = sin(timeValue);

		///* color
		int vertexColorLocation = glGetUniformLocation(shader->getID(), "muxColor");
		glUniform4f(vertexColorLocation, temp + 0.1, temp, temp - 0.1, (temp / 2.0f));

		///* transform
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, timeValue, glm::vec3(1.0, 1.0, 1.0));
		trans = glm::scale(trans, glm::vec3(temp, temp, temp));
		shader->setMat4("boxTransform", trans);

		shader->setMat4("modelMat", modelMat);
		shader->setMat4("viewMat", viewMat);
		shader->setMat4("projectionMat", projectionMat);



		render.draw();
	}
	return -1;
}

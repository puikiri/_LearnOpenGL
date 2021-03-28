
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
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

unsigned int vertices1indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
};
int main()
{
	Render render;


	///* shader
	std::shared_ptr<Shader> shader = std::make_shared<Shader>("../LearnOpenGL/resource/shader/box.vs", "../LearnOpenGL/resource/shader/box.fs");
	std::shared_ptr<RenderObject> ro2 = std::make_shared<RenderObject>(shader);
	ro2->createEBORenderObject(vertices1, sizeof(vertices1), vertices1indices, sizeof(vertices1indices), 0, 3, false, 8, 0);
	ro2->attachVertexAttribPointer(1, 3, false, 8, 3);
	ro2->attachVertexAttribPointer(2, 2, false, 8, 6);
	ro2->setDrawVerNum(6);
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

		render.draw();
	}
	return -1;
}

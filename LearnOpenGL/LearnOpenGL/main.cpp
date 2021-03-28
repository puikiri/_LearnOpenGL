
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
	// 一参 指定2d纹理为对象。
	// 二参 s => x轴，t => y轴。
	// 第三个参数 对齐方式：GL_REPEAT 重复，GL_MIRRORED_REPEAT 镜像，GL_CLAMP_TO_EDGE 边缘拉伸，GL_CLAMP_TO_BORDER 不干嘛。
	/*
		使用 GL_CLAMP_TO_BORDER,则还需要指定边缘色，使用 glTexParameterfv指定
			float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// 纹理过滤：处理拉伸/压缩的纹理取样
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // 多级纹理用
	/*
		第二个参数：
			GL_TEXTURE_MIN_FILTER 压缩/缩小
			GL_TEXTURE_MAG_FILTER 拉伸/放大
		第三个参数：
			GL_NEAREST 领近过滤(只取样不处理)
			GL_LINEAR 线性过滤(取均值/抗锯齿)
			..
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels; // nrChannels 颜色通道。
	stbi_set_flip_vertically_on_load(true); // 图片坐标轴和shader坐标轴对齐
	unsigned char *data = stbi_load("../LearnOpenGL/resource/texture/texture_unhell.png", &width, &height, &nrChannels, 0); 
	// 注意！！！这里有坑！！！！这里的图片要用正常图片，比如png手动改后缀成jpg是会崩掉的！！！其他类似
	stbi_set_flip_vertically_on_load(false);
	unsigned int sourceColorType = GL_RGB;
	if (nrChannels == 4)
		sourceColorType = GL_RGBA;
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, sourceColorType, width, height, 0, sourceColorType, GL_UNSIGNED_BYTE, data);
		// 注意！！！这里有坑！！！！源图的（sourceColorType）RGBA颜色/格式之类的一定要对上！！！，不然会出现很奇怪的图片(上一个的a被下一个rgb取到了)
		/*
		目标纹理对象-多级渐变级别-颜色模式-纹理宽-高-就是0-数据类型-数据(load出来的图像数据)
		*/
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("wocao ! where the jpg ??? \n");
	}
	stbi_image_free(data); // 纹理图像和shader的fs/vs一样，用完可删(已读入内存)。


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

	// 设置东西对应的混合
	shader->active(); // 注意，需要先激活要设置的shader在设置，不然会不知道设置到哪里去。
	shader->setInt("baseTexture", 0);
	shader->setInt("mixTexture", 1);
	shader->deactive();
	// 混合两个图在同一个纹理单元上（用在同一个fs上）
	glActiveTexture(GL_TEXTURE0);// 在绑定纹理之前需要先激活纹理单元 
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

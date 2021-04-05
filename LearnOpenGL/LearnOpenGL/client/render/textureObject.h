#ifndef TEXTURE_OBJECT_H
#define TEXTURE_OBJECT_H

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif
#include "../../core/include.h"

class TextureObject
{
public:
	enum textureWarp {
		GLREPEAT,
		GLMIRROREDREPEAT,
		GLCLAMPTOEDGE,
		GLCLAMPTOBORDER
	};
	enum textureFilter {
		GLNEAREST,
		GLLINEAR,
	};

	TextureObject(std::string source, bool vertically_on_load = true);
	~TextureObject();

	unsigned int getTextureId() { return texId; };
	int getWidth() { return width; };
	int getHeight() { return height; };
	int getRgbChannels() { return rghChannels; };
	std::string getSourceDir() { return sourceDir; };
	void bind() { glBindTexture(GL_TEXTURE_2D, texId); };
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
	///* st ： 0=s, 其他为t
	void setWarp(unsigned int st, unsigned int warpNum);
	///* min mag ： 0=min, 其他为mag
	void setFilter(unsigned int st, unsigned int warpNum);
private:
	int getColor(unsigned int rghChannels)
	{
		if (rghChannels == 4)
			return GL_RGBA;
		return GL_RGB;
	}

public:

private:
	unsigned int texId;
	int width;
	int height;
	int rghChannels; // 颜色通道。
	std::string sourceDir;
};

TextureObject::TextureObject(std::string source, bool vertically_on_load)
{
	///* open GL 是个状态机，当前bind了什么texture，就会用什么texture。shader同理，当前启用什么就用什么。
	glGenTextures(1, &texId);
	bind();
	stbi_set_flip_vertically_on_load(vertically_on_load); // 图片坐标轴和shader坐标轴对齐
	const char* temp = source.c_str();
	unsigned char *data = stbi_load(temp, &width, &height, &rghChannels, 0);
	// 注意！！！这里有坑！！！！这里的图片要用正常图片，比如png手动改后缀成jpg是会崩掉的！！！其他类似
	stbi_set_flip_vertically_on_load(false);
	int sourceColorType = getColor(rghChannels);
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
		printf("wocao ! where the jpg ??? sourceDir : %s \n", sourceDir.c_str());
	}
	stbi_image_free(data); // 纹理图像和shader的fs/vs一样，用完可删(已读入内存)。
	sourceDir = source;
	unbind();
}

void TextureObject::setWarp(unsigned int st, unsigned int warpNum)
{
	auto targetST = GL_TEXTURE_WRAP_S;
	if (st != 0)
		targetST = GL_TEXTURE_WRAP_T;
	if (warpNum == textureWarp::GLREPEAT)
		glTexParameteri(GL_TEXTURE_2D, targetST, GL_CLAMP_TO_EDGE);
	else if (warpNum == textureWarp::GLMIRROREDREPEAT)
		glTexParameteri(GL_TEXTURE_2D, targetST, GL_MIRRORED_REPEAT);
	else if (warpNum == textureWarp::GLCLAMPTOEDGE)
		glTexParameteri(GL_TEXTURE_2D, targetST, GL_CLAMP_TO_EDGE);
	else if (warpNum == textureWarp::GLCLAMPTOBORDER)
		glTexParameteri(GL_TEXTURE_2D, targetST, GL_CLAMP_TO_BORDER);
	/*
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	一参 指定2d纹理为对象。
	二参 s => x轴，t => y轴。
	三参 对齐方式：GL_REPEAT 重复，GL_MIRRORED_REPEAT 镜像，GL_CLAMP_TO_EDGE 边缘拉伸，GL_CLAMP_TO_BORDER 不干嘛。

	使用 GL_CLAMP_TO_BORDER,则还需要指定边缘色，使用 glTexParameterfv指定
			float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	*/
}

void TextureObject::setFilter(unsigned int st, unsigned int warpNum)
{
	auto targetST = GL_TEXTURE_MIN_FILTER;
	if (st != 0)
		targetST = GL_TEXTURE_MAG_FILTER;
	if (warpNum == textureFilter::GLNEAREST)
		glTexParameteri(GL_TEXTURE_2D, targetST, GL_NEAREST);
	else if (warpNum == textureFilter::GLLINEAR)
		glTexParameteri(GL_TEXTURE_2D, targetST, GL_LINEAR);
	/*
	// 纹理过滤：处理拉伸/压缩的纹理取样
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // 多级纹理用
		第二个参数：
			GL_TEXTURE_MIN_FILTER 压缩/缩小
			GL_TEXTURE_MAG_FILTER 拉伸/放大
		第三个参数：
			GL_NEAREST 领近过滤(只取样不处理)
			GL_LINEAR 线性过滤(取均值/抗锯齿)
			..
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
}

TextureObject::~TextureObject()
{
	glDeleteTextures(1, &texId);
}

#endif
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
	///* st �� 0=s, ����Ϊt
	void setWarp(unsigned int st, unsigned int warpNum);
	///* min mag �� 0=min, ����Ϊmag
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
	int rghChannels; // ��ɫͨ����
	std::string sourceDir;
};

TextureObject::TextureObject(std::string source, bool vertically_on_load)
{
	///* open GL �Ǹ�״̬������ǰbind��ʲôtexture���ͻ���ʲôtexture��shaderͬ����ǰ����ʲô����ʲô��
	glGenTextures(1, &texId);
	bind();
	stbi_set_flip_vertically_on_load(vertically_on_load); // ͼƬ�������shader���������
	const char* temp = source.c_str();
	unsigned char *data = stbi_load(temp, &width, &height, &rghChannels, 0);
	// ע�⣡���������пӣ������������ͼƬҪ������ͼƬ������png�ֶ��ĺ�׺��jpg�ǻ�����ģ�������������
	stbi_set_flip_vertically_on_load(false);
	int sourceColorType = getColor(rghChannels);
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
		printf("wocao ! where the jpg ??? sourceDir : %s \n", sourceDir.c_str());
	}
	stbi_image_free(data); // ����ͼ���shader��fs/vsһ���������ɾ(�Ѷ����ڴ�)��
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
	һ�� ָ��2d����Ϊ����
	���� s => x�ᣬt => y�ᡣ
	���� ���뷽ʽ��GL_REPEAT �ظ���GL_MIRRORED_REPEAT ����GL_CLAMP_TO_EDGE ��Ե���죬GL_CLAMP_TO_BORDER �����

	ʹ�� GL_CLAMP_TO_BORDER,����Ҫָ����Եɫ��ʹ�� glTexParameterfvָ��
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
	// ������ˣ���������/ѹ��������ȡ��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // �༶������
		�ڶ���������
			GL_TEXTURE_MIN_FILTER ѹ��/��С
			GL_TEXTURE_MAG_FILTER ����/�Ŵ�
		������������
			GL_NEAREST �������(ֻȡ��������)
			GL_LINEAR ���Թ���(ȡ��ֵ/�����)
			..
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
}

TextureObject::~TextureObject()
{
	glDeleteTextures(1, &texId);
}

#endif
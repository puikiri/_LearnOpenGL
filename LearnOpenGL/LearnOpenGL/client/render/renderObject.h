#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "../shader/shader.h"

class RenderObject
{
public:
	RenderObject(std::shared_ptr<Shader> _shader = nullptr);
	~RenderObject();
	void draw();
	void attachShader(std::shared_ptr<Shader>_shader) { shader = _shader; };
	void clearShader() { shader = nullptr; };
	std::shared_ptr<Shader> getShader() { return shader; };
	void createVBORenderObject(float vertices[], int verticesSize, int locationIndex = 0, int vecSize = 3, bool normalized = false, int verStep = 3, int verOffset = 0);
	void createEBORenderObject(float vertices[], int verticesSize, unsigned int indices[], int indicesSize, int locationIndex = 0, int vecSize = 3, bool normalized = false, int verStep = 3, int verOffset = 0);
	void attachVertexAttribPointer(int locationIndex = 0, int vecSize = 3, bool normalized = false, int verStep = 3, int verOffset = 0);
	std::string  getName() { return name; };
	void setDrawVerNum(unsigned int num) { verNum = num; };
	void setDrawVerOffset(unsigned int offset) { verOffset = offset; };
private:

public:

private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	std::shared_ptr<Shader> shader;
	bool isEBO = false;
	unsigned int verNum = 0;
	unsigned int verOffset = 0;
	std::string name;
};

RenderObject::RenderObject(std::shared_ptr<Shader> _shader)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	name = std::string("renderObject_VAO=").append(std::to_string(VAO)).append("_VBO=").append(std::to_string(VBO)).append("_EBO=").append(std::to_string(EBO));
	shader = _shader;
}

RenderObject::~RenderObject()
{
	shader = nullptr;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void RenderObject::draw()
{
	if(shader)
		shader->active();
	glBindVertexArray(VAO);
	if(isEBO)
		glDrawElements(GL_TRIANGLES, verNum, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, verOffset, verNum);
	glBindVertexArray(0);
	if (shader)
		shader->deactive();
}

void RenderObject::createVBORenderObject(float vertices[], int verticesSize, int locationIndex, int vecSize, bool normalized, int verStep, int verOffset)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	attachVertexAttribPointer(locationIndex, vecSize, normalized, verStep, verOffset);
	isEBO = false;
}

void RenderObject::createEBORenderObject(float vertices[], int verticesSize, unsigned int indices[], int indicesSize, int locationIndex, int vecSize, bool normalized, int verStep, int verOffset)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
	attachVertexAttribPointer(locationIndex, vecSize, normalized, verStep, verOffset);
	isEBO = true;
}

void RenderObject::attachVertexAttribPointer(int locationIndex, int vecSize, bool normalized, int verStep, int verOffset)
{
	glVertexAttribPointer(locationIndex, vecSize, GL_FLOAT, normalized ? GL_TRUE : GL_FALSE, verStep * sizeof(float), (void*)(verOffset * sizeof(float)));
	glEnableVertexAttribArray(locationIndex);
}

#endif
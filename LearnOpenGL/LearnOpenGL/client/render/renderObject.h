#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "../shader/shader.h"
#include "renderBase.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RenderObject:public virtual RenderBase
{
public:
	RenderObject(std::shared_ptr<Shader> _shader = nullptr);
	~RenderObject();
	virtual void beforeRender();
	virtual void render();
	virtual void afterRender();

	void attachShader(std::shared_ptr<Shader>_shader) { shader = _shader; };
	void clearShader() { shader = nullptr; };
	std::shared_ptr<Shader> getShader() { return shader; };
	void createVBORenderObject(float vertices[], int verticesSize, int locationIndex = 0, int vecSize = 3, bool normalized = false, int verStep = 3, int verOffset = 0);
	void createEBORenderObject(float vertices[], int verticesSize, unsigned int indices[], int indicesSize, int locationIndex = 0, int vecSize = 3, bool normalized = false, int verStep = 3, int verOffset = 0);
	void attachVertexAttribPointer(int locationIndex = 0, int vecSize = 3, bool normalized = false, int verStep = 3, int verOffset = 0);
	std::string  getName() { return name; };
	void setDrawVerNum(unsigned int num) { verNum = num; };
	void setDrawVerOffset(unsigned int offset) { verOffset = offset; };

	void setTransform(std::string name, glm::mat4 m4) { shaderTransform[name] = m4; };
	glm::mat4 getTransform(std::string name) { return shaderTransform[name]; };
	void resetTransforms() { shaderTransform.clear(); };

	void setShaderV4(std::string name, glm::vec4 m4) { shaderV4Prop[name] = m4; };
	glm::vec4 getShaderV4(std::string name) { return shaderV4Prop[name]; };
	void resetShaderV4s() { shaderV4Prop.clear(); };

	void setShaderV3(std::string name, glm::vec3 m4) { shaderV3Prop[name] = m4; };
	glm::vec3 getShaderV3(std::string name) { return shaderV3Prop[name]; };
	void resetShaderV3s() { shaderV3Prop.clear(); };

	void setShaderFloat(std::string name, float m4) { shaderFloatProp[name] = m4; };
	float getShaderFloat(std::string name) { return shaderFloatProp[name]; };
	void resetShaderFloats() { shaderFloatProp.clear(); };

	void setPosition(glm::vec3 pos) { position = pos; };
	glm::vec3 getPosition() { return position; };
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
	glm::vec3 position;
	std::map<std::string, glm::mat4> shaderTransform;
	std::map<std::string, glm::vec4> shaderV4Prop;
	std::map<std::string, glm::vec3> shaderV3Prop;
	std::map<std::string, float> shaderFloatProp;
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

void RenderObject::beforeRender()
{
}

void RenderObject::render()
{
	if (shader)
	{
		shader->active();
		shader->bindTexture();
		for(auto temp : shaderTransform)
			shader->setMat4(temp.first, temp.second);
		for (auto temp : shaderV4Prop)
			shader->setVec4(temp.first, temp.second);
		for (auto temp : shaderV3Prop)
			shader->setVec3(temp.first, temp.second);
		for (auto temp : shaderFloatProp)
			shader->setFloat(temp.first, temp.second);
	}
	glBindVertexArray(VAO);
	if (isEBO)
		glDrawElements(GL_TRIANGLES, verNum, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, verOffset, verNum);
	glBindVertexArray(0);
	if (shader)
	{
		shader->unbindTexture();
		shader->deactive();
	}
}

void RenderObject::afterRender()
{
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
#ifndef TEST_SENCE_H
#define TEST_SENCE_H

#include "../shader/shader.h"

float vertices1[] = {
	-0.4f, -0.4f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.4f, -0.4f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f,
};

float vertices2[] = {
	0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.8f, 0.7f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.7f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.7f, 0.8f, 0.0f, 0.5f, 0.5f, 0.5f
};

unsigned int vertices2indices[] = {
	0, 1, 3,
	1, 2, 3,
	0, 2, 3
};

class TestSence
{
public:
	TestSence();
	~TestSence();
	void draw();

private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	Shader* shader;
};

TestSence::TestSence()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); 

	shader = new Shader("../LearnOpenGL/resource/shader/ShiningDelta.vs","../LearnOpenGL/resource/shader/ShiningDelta.fs");
}

TestSence::~TestSence()
{
}

void TestSence::draw()
{
	shader->active();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices2indices), vertices2indices, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	float timeValue = glfwGetTime();
	int vertexColorLocation = glGetUniformLocation(shader->getID(), "muxColor");
	glUniform4f(vertexColorLocation, sin(timeValue) + 0.1, sin(timeValue), sin(timeValue) - 0.1, (sin(timeValue) / 2.0f));
	shader->deactive();
}

#endif
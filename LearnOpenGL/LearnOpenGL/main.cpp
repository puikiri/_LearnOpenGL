
#include "client/render/render.h"
#include "client/render/renderObject.h"

bool loop = true;
bool checkLoop()
{
	return loop;
}

void setLoop(bool lp)
{
	loop = lp;
}

float vertices1[] = {
	-0.4f, -0.4f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.4f, -0.4f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.4f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.4f, 0.4f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f,
};

unsigned int vertices1indices[] = {
	0, 1, 2,
	3, 4, 5,
};

int main()
{
	Render render;

	std::shared_ptr<Shader> shader = std::make_shared<Shader>("../LearnOpenGL/resource/shader/ShiningDelta.vs", "../LearnOpenGL/resource/shader/ShiningDelta.fs");
	std::shared_ptr<RenderObject> ro2 = std::make_shared<RenderObject>(shader);
	ro2->createEBORenderObject(vertices1, sizeof(vertices1), vertices1indices, sizeof(vertices1indices), 0, 3, false, 6, 0);
	ro2->attachVertexAttribPointer(1, 3, false, 6, 3);
	ro2->setDrawVerNum(6);
	render.gerRenderWorld()->regRenderObject(ro2->getName(), ro2);
	while (checkLoop())
	{
		float timeValue = glfwGetTime();
		int vertexColorLocation = glGetUniformLocation(shader->getID(), "muxColor");
		glUniform4f(vertexColorLocation, sin(timeValue) + 0.1, sin(timeValue), sin(timeValue) - 0.1, (sin(timeValue) / 2.0f));

		render.draw();
	}
	return -1;
}

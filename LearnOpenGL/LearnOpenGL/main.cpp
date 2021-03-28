
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

//float vertices2[] = {
//	0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f,
//	0.8f, 0.7f, 0.0f, 0.0f, 1.0f, 0.0f,
//	0.7f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f,
//	0.7f, 0.8f, 0.0f, 0.5f, 0.5f, 0.5f
//};
//
//unsigned int vertices2indices[] = {
//	0, 1, 3,
//	1, 2, 3,
//	0, 2, 3
//};



int main()
{
	Render render;

	std::shared_ptr<Shader> shader = std::make_shared<Shader>("../LearnOpenGL/resource/shader/ShiningDelta.vs", "../LearnOpenGL/resource/shader/ShiningDelta.fs");
	std::shared_ptr<RenderObject> ro1 = std::make_shared<RenderObject>(shader);
	ro1->createVBORenderObject(vertices1, sizeof(vertices1), 0, 3, false, 6, 0);
	ro1->attachVertexAttribPointer(1, 3, false, 6, 3);
	ro1->setDrawVerNum(6);
	/*std::shared_ptr<RenderObject> ro2 = std::make_shared<RenderObject>(shader);
	ro2->createEBORenderObject(vertices2, sizeof(vertices2), vertices2indices, sizeof(vertices2indices), 0, 3, false, 6, 0);
	ro2->attachVertexAttribPointer(1, 3, false, 6, 3);
	ro2->setDrawVerNum(9);*/
	render.gerRenderWorld()->regRenderObject(ro1->getName(), ro1);
	//render.gerRenderManager()->regRenderObject(ro2->getName(), ro2);
	while (checkLoop())
	{
		float timeValue = glfwGetTime();
		int vertexColorLocation = glGetUniformLocation(shader->getID(), "muxColor");
		glUniform4f(vertexColorLocation, sin(timeValue) + 0.1, sin(timeValue), sin(timeValue) - 0.1, (sin(timeValue) / 2.0f));

		render.draw();
	}
	return -1;
}

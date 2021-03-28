//#pragma once
//#include "core/include.h"
//
//const unsigned int vertices1Size = 18;
//float vertices1[vertices1Size] = {
//	-0.4f, -0.4f, 0.0f,
//	0.4f, -0.4f, 0.0f,
//	0.f, 0.7f, 0.0f,
//	-0.4f, 0.4f, 0.0f,
//	0.4f, 0.4f, 0.0f,
//	0.f, -0.7f, 0.0f
//};
//float vertices1_2[vertices1Size] = {
//	-0.6f, -0.6f, 0.0f,
//	0.2f, -0.6f, 0.0f,
//	-0.2f, 0.5f, 0.0f,
//	-0.6f, 0.2f, 0.0f,
//	0.2f, 0.2f, 0.0f,
//	-0.2f, -0.9f, 0.0f
//};
//
//float vertices2[] = {
//	0.8f, 0.8f, 0.0f,
//	0.8f, 0.7f, 0.0f,
//	0.7f, 0.7f, 0.0f,
//	0.7f, 0.8f, 0.0f
//};
//
//unsigned int vertices2indices[] = {
//	0, 1, 3,
//	1, 2, 3,
//	0, 2, 3
//};
//
//unsigned int VBO;
//unsigned int VAO;
//unsigned int EBO;
//unsigned int shaderProgram;
//const unsigned int vertexShaderLocation = 0;
//
//std::string getVertexShaderStr(const char* location)
//{
//	std::string ret = "";
//	ret.append("#version 330 core\n ");
//	ret.append("layout (location = ").append(location).append(") in vec3 aPos;\n ");
//	ret.append("void main()\n ");
//	ret.append("{\n ");
//	ret.append(" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n ");
//	ret.append("}\n ");
//	return ret;
//}
//
//std::string getFragmentShadeStr(const char* location)
//{
//	std::string ret = "";
//	ret.append("#version 330 core\n");
//	//ret.append("in vec3 icolor;\n");
//	//ret.append("layout (location = ").append(location).append(") in vec3 icolor;\n ");
//	ret.append("out vec4 ocolor;\n");
//	ret.append("void main()\n");
//	ret.append("{\n ");
//	//ret.append(" ocolor = vec4(icolor.r, icolor.g, icolor.b, 1.0f);\n");
//	ret.append(" ocolor = vec4(0.5f, 0.35f, 0.8f, 1.0f);\n");
//	ret.append("}\n ");
//	return ret;
//}
//
//void checkCompileShader(unsigned int shader, const char* compileName)
//{
//	int  success;
//	char infoLog[512];
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		printf("A xi ba !!!!! compile shader wrong : %s\n", compileName);
//		printf(infoLog);
//	}
//}
//
//void checkLinkShaderProgram(unsigned int shader, const char* linkName)
//{
//	int  success;
//	char infoLog[512];
//	glGetProgramiv(shader, GL_LINK_STATUS, &success);
//	if (!success)
//	{
//		glGetProgramInfoLog(shader, 512, NULL, infoLog);
//		printf("A xi ba !!!!! link shader wrong : %s \n", linkName);
//		printf(infoLog);
//	}
//}
//
//bool initShader()
//{
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	std::string vertexShaderStr = getVertexShaderStr(std::to_string(vertexShaderLocation).c_str());
//	auto vertexShaderCStr = vertexShaderStr.c_str();
//	glShaderSource(vertexShader, 1, &vertexShaderCStr, NULL);
//	glCompileShader(vertexShader);
//	checkCompileShader(vertexShader, "vertexShader");
//
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	std::string fragmentShaderStr = getFragmentShadeStr(std::to_string(vertexShaderLocation).c_str());
//	auto fragmentShaderCStr = fragmentShaderStr.c_str();
//	glShaderSource(fragmentShader, 1, &fragmentShaderCStr, NULL);
//	glCompileShader(fragmentShader);
//	checkCompileShader(fragmentShader, "fragmentShader");
//
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	checkLinkShaderProgram(shaderProgram, "shaderProgram");
//	glUseProgram(shaderProgram);
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//	return true;
//}
//
//void drawStarOfDavid(int rotate = 0)
//{
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STREAM_DRAW);
//	glVertexAttribPointer(vertexShaderLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1_2), vertices1_2, GL_STREAM_DRAW);
//	glVertexAttribPointer(vertexShaderLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(vertexShaderLocation);
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STREAM_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices2indices), vertices2indices, GL_STREAM_DRAW);
//	glVertexAttribPointer(vertexShaderLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(vertexShaderLocation);
//	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	{
//	//// 1. �󶨶�������VAO�� ����Ҫ�󣬲��󲻸���Ⱦ�İ���
//	//glBindVertexArray(VAO);
//	//// 2. �󶨶��㻺�壬����Ҫ�󣬲���û�ض���/ȡbufferData��
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//// 3. ���ƶ�����������ݵ������и�OpenGL�ã�
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STREAM_DRAW);
//	//// 4. ���ö�������ָ�룬
//	//// ��λ������ɫ���汾��||һ����3(��������������)||������������||�Ƿ��һ��(Normalize)||ͬ2�����||�����ڴ�ƫ��
//	//glVertexAttribPointer(vertexShaderLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	//// 5. ����location��vertexShaderLocationλ
//	//glEnableVertexAttribArray(vertexShaderLocation);
//	//// 5.? ����в�ͬ�Ķ������ݲ��ò�ͬ����ɫ��������£���ô��Drawǰ�����Ե�����任shader
//	//// glUseProgram(shaderProgram);
//	//// End. Draw and UnBind
//	//glDrawArrays(GL_TRIANGLES, 0, 6); // �˴���6�ǻ�6����,������0��ʼ��
//	//// 6. �����Ҫ(�����л���������/����BUFF)����ô���Ե���������֮�������°󶨡�
//	///*
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindVertexArray(0);
//	//*/
//	//// ע���˴��ϲ�����¾Ͳ��ð�
//	///*
//	//glBindVertexArray(VAO);
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//*/
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STREAM_DRAW);
//	//// 3. �������������˵ֱ�׵�����������߳���Ӧ����ô ƴ���㻺���ڵ����ݡ�
//	//// �ٸ����ӣ����������ĸ��㣬�ҿ���ͨ��ָ���������������߳��򣬿�����Щ��ƴ����ƴ����ȷ��ͼԪ��
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//// 4. ������
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices2indices), vertices2indices, GL_STREAM_DRAW);
//	//glVertexAttribPointer(vertexShaderLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	//glEnableVertexAttribArray(vertexShaderLocation);
//	//// End. Draw and UnBind
//	//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // �˴���9�ǻ�9���㣬���һ���������������飿һ��0���ɡ�
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//glBindVertexArray(0);
//	}
//}
//
//
//
//

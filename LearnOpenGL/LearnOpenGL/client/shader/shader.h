#ifndef SHADER_H
#define SHADER_H

#include "../../core/include.h"
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader(std::string vsPath, std::string fsPath);
	~Shader() { glDeleteProgram(shaderId); };
	inline unsigned int getID() const { return shaderId; }
	inline void active() { glUseProgram(shaderId); };
	inline void deactive() { glDeleteProgram(shaderId); };
	inline void setBool(const std::string &name, bool value) const { glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);  };
	inline void setInt(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value); };
	inline void setFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value); };
private:
	Shader() { };
	void checkCompileShader(unsigned int shader, const char* compileName);
	void checkLinkShaderProgram(unsigned int shader, const char* linkName);
public:

private:
	unsigned int shaderId;
};

Shader::Shader(std::string vsPath, std::string fsPath)
{
	std::stringstream vsSStream, fsSStream;
	std::ifstream vsStream, fsStream;
	std::string vsCode, fsCode;
	vsStream.open(vsPath);
	vsSStream << vsStream.rdbuf();
	vsStream.close();
	vsCode = vsSStream.str();
	Assert(!vsCode.empty(), "dame it !!!!! vs load error !!!!!")
	fsStream.open(fsPath);
	fsSStream << fsStream.rdbuf();
	fsStream.close();
	fsCode = fsSStream.str();
	Assert(!fsCode.empty(), "dame it !!!!! fs load error !!!!!");

	const char* vsCodeC = vsCode.c_str();
	const char* fsCodeC = fsCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vsCodeC, NULL);
	glCompileShader(vertexShader);
	checkCompileShader(vertexShader, vsPath.c_str());

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fsCodeC, NULL);
	glCompileShader(fragmentShader);
	checkCompileShader(fragmentShader, fsPath.c_str());

	shaderId = glCreateProgram();
	glAttachShader(shaderId, vertexShader);
	glAttachShader(shaderId, fragmentShader);
	glLinkProgram(shaderId);
	checkLinkShaderProgram(shaderId, "shaderProgram");

	//glUseProgram(shaderProgram);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::checkCompileShader(unsigned int shader, const char* compileName)
{
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("A xi ba !!!!! compile shader wrong : %s\n", compileName);
		printf(infoLog);
	}
}

void Shader::checkLinkShaderProgram(unsigned int shader, const char* linkName)
{
	int  success;
	char infoLog[512];
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		printf("A xi ba !!!!! link shader wrong : %s \n", linkName);
		printf(infoLog);
	}
}
#endif
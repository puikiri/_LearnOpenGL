#ifndef SHADER_H
#define SHADER_H

#include "../../core/include.h"
#include "../../core/file.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	inline void setMat4(const std::string &name, glm::mat4 value, int matCount = 1, bool transpose = false) const {
	//								二参：传入矩阵数，三参：是否转置(用于系统和gl的横竖不对齐的问题)
		glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), matCount, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
	};
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
	std::string vs = File::readFileData(vsPath);
	std::string fs = File::readFileData(fsPath);
	const char* vsCodeC = vs.c_str();
	const char* fsCodeC = fs.c_str();

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
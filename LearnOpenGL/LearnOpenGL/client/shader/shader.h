#ifndef SHADER_H
#define SHADER_H

#include "../../core/include.h"
#include "../../core/file.h"
#include "../render/textureManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>

class Shader
{
public:
	Shader(std::string vsPath, std::string fsPath);
	~Shader();
	inline unsigned int getID() const { return shaderId; }
	inline void active() { glUseProgram(shaderId); };
	inline void deactive() { /*glDeleteProgram(0);*/ };
	inline void setBool(const std::string &name, bool value) const { glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int)value);  };
	inline void setInt(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value); };
	inline void setFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value); };
	inline void setMat4(const std::string &name, glm::mat4 value, int matCount = 1, bool transpose = false) const {
	//								二参：传入矩阵数，三参：是否转置(用于系统和gl的横竖不对齐的问题)
		glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), matCount, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
	};
	void setTexture(unsigned int activeTexNum, std::string texUniformKey, std::string texSource);
	void delTexture(unsigned int activeTexNum);
	void bindTexture();
	void unbindTexture();
private:
	Shader() { };
	void checkCompileShader(unsigned int shader, const char* compileName);
	void checkLinkShaderProgram(unsigned int shader, const char* linkName);
public:

private:
	unsigned int shaderId;
	std::map<unsigned int, std::pair<unsigned int, std::string>> texs; // key : 纹理单元位置, value-key : texId, value-value ：shader texture uniform
	TextureManager* texMgr;
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

	texMgr = TextureManager::instance();
}

Shader::~Shader() {
	texMgr = nullptr;
	texs.clear();
	glDeleteProgram(shaderId);
};

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

void Shader::setTexture(unsigned int activeTexNum, std::string texUniformKey, std::string texSource)
{
	auto temp = texs.find(activeTexNum);
	if (temp != texs.end() && (temp->second.second == texUniformKey) && (texMgr->getTexture(temp->second.first)->getSourceDir() == texSource))
		return;

	// 设置东西对应的混合
	active(); // 注意，需要先激活要设置的shader在设置，不然会不知道设置到哪里去。
	auto tempTexture = texMgr->getTexture(texSource);
	unsigned int texId = tempTexture ? tempTexture->getTextureId() : texMgr->createTexture(texSource);

	setInt(texUniformKey, activeTexNum);// 注：这里的 texUniformKey 对应的是下面激活的纹理单元的 GL_TEXTURE0/GL_TEXTURE1..
	// 混合两个图在同一个纹理单元上（用在同一个fs上）时，多次设置texs到同一shader的不同纹理单眼上。
	texs[activeTexNum] = std::make_pair(texId, texUniformKey);

	deactive();
}

void Shader::delTexture(unsigned int activeTexNum)
{
	texs.erase(activeTexNum);
}

void Shader::bindTexture()
{
	for (auto temp : texs)
	{
		glActiveTexture(GL_TEXTURE0 + temp.first);// 在绑定纹理之前需要先激活纹理单元 
		glBindTexture(GL_TEXTURE_2D, temp.second.first);
	}
}

void Shader::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}
#endif
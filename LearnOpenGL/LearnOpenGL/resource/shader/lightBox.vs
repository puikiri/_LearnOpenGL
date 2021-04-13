#version 330 core
layout (location = 0) in vec3 pos; // 顶点位置（局部）
layout (location = 1) in vec3 normal; // 法向量（局部）
layout (location = 2) in vec2 inTexCoord; // 纹理位置(s,t)

out vec2 TexCoord;
out vec3 Normal; // 法向量(世界)
out vec3 FragPos;  // 顶点位置(世界)

uniform mat4 transform; // all变换矩阵
uniform mat4 modelMat; // model变换矩阵

void main()
{
	gl_Position = transform * vec4(pos, 1.0);
    TexCoord = inTexCoord;
	Normal = mat3(transpose(inverse(modelMat))) * normal; // 法向量需要 使用inverse和transpose函数自己生成法线矩阵 来特殊处理，具体百度
	FragPos = vec3(modelMat * vec4(pos, 1.0));
}

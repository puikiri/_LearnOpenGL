#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal; // 顶点属性
layout (location = 2) in vec2 inTexCoord; // 纹理位置(s,t)

out vec2 TexCoord;

uniform mat4 transform; // 变换矩阵

void main()
{
	gl_Position = transform * vec4(pos, 1.0);
    TexCoord = inTexCoord;
}

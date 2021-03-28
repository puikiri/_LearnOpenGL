#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 inTexCoord; // 纹理位置(s,t)
out vec4 vertexColor;
out vec2 TexCoord;
uniform mat4 boxTransform; // 变换矩阵

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
	// 注意：变化矩阵是从右往左乘的。
	gl_Position = projectionMat * viewMat * modelMat * boxTransform * vec4(pos, 1.0);
	//gl_Position = vec4(pos, 1.0);
	vertexColor = vec4(color, 1.0);
    TexCoord = inTexCoord;
}

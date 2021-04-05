#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color; // 由于使用的是和lightBox同一顶点，故此处是法向量.....
layout (location = 2) in vec2 inTexCoord; // 纹理位置(s,t)
out vec4 vertexColor;
out vec2 TexCoord;

uniform mat4 transform; // all变换矩阵

void main()
{
	gl_Position = transform * vec4(pos, 1.0);
	vertexColor = vec4(color, 1.0);
    TexCoord = inTexCoord;
}

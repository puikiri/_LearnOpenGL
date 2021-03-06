#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 inTexCoord; // ����λ��(s,t)
out vec4 vertexColor;
out vec2 TexCoord;

uniform mat4 transform; // �任����

void main()
{
	gl_Position = transform * vec4(pos, 1.0);
	//gl_Position = vec4(pos, 1.0);
	vertexColor = vec4(color, 1.0);
    TexCoord = inTexCoord;
}

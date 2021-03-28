#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 inTexCoord; // Œ∆¿ÌŒª÷√(s,t)
out vec4 vertexColor;
out vec2 TexCoord;
uniform mat4 boxTransform; // ±‰ªªæÿ’Û
void main()
{
	gl_Position = boxTransform * vec4(pos, 1.0);
	//gl_Position = vec4(pos, 1.0);
	vertexColor = vec4(color, 1.0);
    TexCoord = inTexCoord;
}

#version 330 core
in vec4 vertexColor;
out vec4 FragColor;

uniform vec4 muxColor;

void main()
{
	float r = vertexColor.x + muxColor.x;
	if(r > 1.0)
		r-=1.0;
	float g = vertexColor.y + muxColor.y;
	if(g > 1.0)
		g-=1.0;
	float b = vertexColor.z + muxColor.z;
	if(b > 1.0)
		b-=1.0;
	float a = vertexColor.w + muxColor.w;
	if(a > 1.0)
		a-=1.0;
	FragColor = vec4(r, g, b, a);
}


#version 330 core
in vec4 vertexColor;
out vec4 FragColor;
in vec2 TexCoord;

uniform vec4 muxColor;
uniform sampler2D baseTexture;
uniform sampler2D mixTexture;

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
    FragColor = mix(texture(baseTexture, TexCoord), texture(mixTexture, TexCoord), 0.2); // texture(baseTexture, TexCoord); // 0.2 混合位置使用20%第二个纹理的颜色。
	FragColor = FragColor * vec4(r, g, b, a);
}


#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D baseTexture;
uniform vec4 lightColor;

void main()
{
    float minColor = 0.1;
	float r = min(max(vertexColor.x + lightColor.x, minColor), 1);
	float g = min(max(vertexColor.y + lightColor.y, minColor), 1);
	float b = min(max(vertexColor.z + lightColor.z, minColor), 1);
	float a = min(max(vertexColor.w + lightColor.w, minColor), 1);

    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * vec4(r, g, b, a);
}


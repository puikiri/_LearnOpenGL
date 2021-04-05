#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D baseTexture;
uniform vec4 lightColor;

void main()
{
    float ambientStrength = 0.1;
	float r = min(max(vertexColor.x + lightColor.x, ambientStrength), 1);
	float g = min(max(vertexColor.y + lightColor.y, ambientStrength), 1);
	float b = min(max(vertexColor.z + lightColor.z, ambientStrength), 1);
	float a = min(max(vertexColor.w + lightColor.w, ambientStrength), 1);

    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * vec4(r, g, b, a);
}


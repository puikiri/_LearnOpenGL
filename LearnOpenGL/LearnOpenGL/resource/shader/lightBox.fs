#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D baseTexture;
uniform vec4 objectColor;
uniform vec4 lightColor;

void main()
{
	// 模拟环境光照
    float ambientStrength = 0.1;
    vec4 ambient = ambientStrength * lightColor;
    vec4 result = ambient * objectColor;

    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * result;
}


#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D baseTexture;
uniform vec4 lightColor;

void main()
{
    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * vertexColor * lightColor;
}


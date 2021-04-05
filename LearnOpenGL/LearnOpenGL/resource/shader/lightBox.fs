#version 330 core
in vec2 TexCoord;
in vec3 Normal; // ������(����)
in vec3 FragPos; // ����λ�ã����磩
in vec3 LightPos; // �ƹ�λ�ã����磩
in vec3 ViewPos;  // ���λ��(����)

out vec4 FragColor;

uniform sampler2D baseTexture;
uniform vec4 objectColor; // ������ɫ
uniform vec4 lightColor; // �ƹ���ɫ

void main()
{
	// Phong 
	// ģ�⻷������
    float ambientStrength = 0.1; // ������ϵ��
	float specularStrength = 0.5; // �߹�ϵ��
	float specularPow = 32; // �߹ⷴ��ֵ
	///* �ƹ�
	float r = min(max(lightColor.x, ambientStrength), 1);
	float g = min(max(lightColor.y, ambientStrength), 1);
	float b = min(max(lightColor.z, ambientStrength), 1);
	float a = min(max(lightColor.w, ambientStrength), 1);
	vec4 tLightColor = vec4(r, g, b, a);
    vec4 ambient = ambientStrength * tLightColor;

	///* ������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * tLightColor;

	///* �߹�
	vec3 viewDir = normalize(ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularPow);
	vec4 specular = specularStrength * spec * lightColor;

    vec4 result = (ambient + diffuse + specular) * objectColor;

    FragColor = texture(baseTexture, TexCoord); 
	FragColor = FragColor * result;
}

